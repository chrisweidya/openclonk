// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

This is an example illustrating the use of the support vector machine
utilities from the dlib C++ Library.  In particular, we show how to use the
C parametrization of the SVM in this example.

This example creates a simple set of data to train on and then shows
you how to use the cross validation and svm training functions
to find a good decision function that can classify examples in our
data set.


The data used in this example will be 2 dimensional data and will
come from a distribution where points with a distance less than 10
from the origin are labeled +1 and all other points are labeled
as -1.

*/

//Modified by Chris

#include "stdafx.h"
#include <iostream>
#include <dlib/svm.h>
#include <fstream>
#include <sstream>

using namespace std;
using namespace dlib;


int main()
{
	// The svm functions use column vectors to contain a lot of the data on
	// which they operate. So the first thing we do here is declare a convenient
	// typedef.  

	// This typedef declares a matrix with 2 rows and 1 column.  It will be the
	// object that contains each of our 2 dimensional samples.   (Note that if
	// you wanted more than 2 features in this vector you can simply change the
	// 2 to something else.  Or if you don't know how many features you want
	// until runtime then you can put a 0 here and use the matrix.set_size()
	// member function)
	int num_rows = 13;
	int num_cols = 9;
	typedef matrix<double, 9 - 1, 1> sample_type;

	int folds = 4;
	// This is a typedef for the type of kernel we are going to use in this
	// example.  In this case I have selected the radial basis kernel that can
	// operate on our 2D sample_type objects.  You can use your own custom
	// kernels with these tools as well, see custom_trainer_ex.cpp for an
	// example.
	typedef radial_basis_kernel<sample_type> kernel_type;


	// Now we make objects to contain our samples and their respective labels.
	std::vector<sample_type> samples;
	std::vector<double> labels;

	// Now let's put some data into our samples and labels objects.  We do this
	// by looping over a bunch of points and labeling them according to their
	// distance from the origin.


	std::ifstream file("AchSheet.csv");

	for (int row = 0; row < num_rows; ++row)
	{
		std::string line;
		std::getline(file, line);
		if (!file.good())
			break;

		std::stringstream iss(line);
		sample_type samp;
		for (int col = 0; col < num_cols; ++col)
		{
			std::string val;
			std::getline(iss, val, ',');
			std::stringstream convertor(val);
			if (col < num_cols - 1) {
				convertor >> samp(col);
				cout << samp(col) << " inserted into " << col << "\n";
			}
			else {
				int det;
				samples.push_back(samp);
				convertor >> det;
				cout << "pushed " << det << "\n";
				labels.push_back(det);
			}
			if (!iss.good())
				break;
		}

	}
	file.close();
	// Here we normalize all the samples by subtracting their mean and dividing
	// by their standard deviation.  This is generally a good idea since it
	// often heads off numerical stability problems and also prevents one large
	// feature from smothering others.  Doing this doesn't matter much in this
	// example so I'm just doing this here so you can see an easy way to
	// accomplish it.  
	vector_normalizer<sample_type> normalizer;
	// Let the normalizer learn the mean and standard deviation of the samples.
	normalizer.train(samples);
	// now normalize each sample
	for (unsigned long i = 0; i < samples.size(); ++i)
		samples[i] = normalizer(samples[i]);


	// Now that we have some data we want to train on it.  However, there are
	// two parameters to the training.  These are the C and gamma parameters.
	// Our choice for these parameters will influence how good the resulting
	// decision function is.  To test how good a particular choice of these
	// parameters are we can use the cross_validate_trainer() function to perform
	// n-fold cross validation on our training data.  However, there is a
	// problem with the way we have sampled our distribution above.  The problem
	// is that there is a definite ordering to the samples.  That is, the first
	// half of the samples look like they are from a different distribution than
	// the second half.  This would screw up the cross validation process but we
	// can fix it by randomizing the order of the samples with the following
	// function call.
	randomize_samples(samples, labels);


	// here we make an instance of the svm_c_trainer object that uses our kernel
	// type.
	svm_c_trainer<kernel_type> trainer;

	// Now we loop over some different C and gamma values to see how good they
	// are.  Note that this is a very simple way to try out a few possible
	// parameter choices.  You should look at the model_selection_ex.cpp program
	// for examples of more sophisticated strategies for determining good
	// parameter choices.
	cout << "doing cross validation" << endl;

	for (double gamma = 0.00001; gamma <= 1; gamma *= 2)
	{
		for (double C = 1; C < 100000; C *= 2)
		{
			// tell the trainer the parameters we want to use
			trainer.set_kernel(kernel_type(gamma));
			trainer.set_c(C);

			cout << "gamma: " << gamma << "    C: " << C;
			// Print out the cross validation accuracy for 3-fold cross validation using
				// the current gamma and C.  cross_validate_trainer() returns a row vector.
				// The first element of the vector is the fraction of +1 training examples
				// correctly classified and the second number is the fraction of -1	training
				// examples correctly classified.
				cout << " cross validation accuracy: "	<< cross_validate_trainer(trainer, samples, labels, folds);
		}
	}


	// From looking at the output of the above loop it turns out that good
	// values for C and gamma for this problem are 5 and 0.15625 respectively.
	// So that is what we will use.

	// Now we train on the full set of data and obtain the resulting decision
	// function.  The decision function will return values >= 0 for samples it
	// predicts are in the +1 class and numbers < 0 for samples it predicts to
	// be in the -1 class.
//	trainer.set_kernel(kernel_type(0.01024));
//	trainer.set_c(128);
	trainer.set_kernel(kernel_type(0.01)); //round 2
	trainer.set_c(128);
	typedef decision_function<kernel_type> dec_funct_type;
	typedef normalized_function<dec_funct_type> funct_type;

	// Here we are making an instance of the normalized_function object.  This
	// object provides a convenient way to store the vector normalization
	// information along with the decision function we are going to learn.  
	funct_type learned_function;
	learned_function.normalizer = normalizer;  // save normalization information
	learned_function.function = trainer.train(samples, labels); // perform the actual SVM training and save the results

		// print out the number of support vectors in the resulting decision function
		cout << "\nnumber of support vectors in our learned_function is "
		<< learned_function.function.basis_vectors.size() << endl;

	// Now let's try this decision_function on some samples we haven't seen before.
		sample_type sample;


	std::ifstream file2("AchTest.csv");
	num_rows = 4;
	num_cols = 8;
	for (int row = 0; row < num_rows; ++row)
	{
		std::string line;
		std::getline(file2, line);
		if (!file2.good())
			break;

		std::stringstream iss(line);
		for (int col = 0; col < num_cols; ++col)
		{
			std::string val;
			std::getline(iss, val, ',');
			std::stringstream convertor(val);
			convertor >> sample(col);
			std::cout << sample(col) << "test\n";
			if (!iss.good())
				break;
		}

		cout << "This is a ? class example, the classifier output is " << learned_function(sample) << endl;
	}

	file2.close();

		serialize("achievement_result.dat") << learned_function;

	// Now let's open that file back up and load the function object it contains.
		deserialize("achievement_result.dat") >> learned_function;

	// We can also train a decision function that reports a well conditioned
	// probability instead of just a number > 0 for the +1 class and < 0 for the
	// -1 class.  An example of doing that follows:
	typedef probabilistic_decision_function<kernel_type> probabilistic_funct_type;


	typedef normalized_function<probabilistic_funct_type> pfunct_type;

	pfunct_type learned_pfunct;
	learned_pfunct.normalizer = normalizer;
	learned_pfunct.function = train_probabilistic_decision_function(trainer,samples, labels, folds);
	// Now we have a function that returns the probability that a given sample is of the + 1 class.
		// print out the number of support vectors in the resulting decision function. 
		// (it should be the same as in the one above)
		cout << "\nnumber of support vectors in our learned_pfunct is "
		<< learned_pfunct.function.decision_funct.basis_vectors.size() << endl;

	file2.open("AchTest.csv");
	for (int row = 0; row < num_rows; ++row)
	{
		std::string line;
		std::getline(file2, line);
		if (!file2.good())
			break;

		std::stringstream iss(line);
		for (int col = 0; col < num_cols; ++col)
		{
			std::string val;
			std::getline(iss, val, ',');
			std::stringstream convertor(val);
			convertor >> sample(col);
			if (!iss.good())
				break;
		}

		cout << "This is a ? class example, the classifier output is " <<

			learned_pfunct(sample) << endl;
	}

	file2.close();

	// Another thing that is worth knowing is that just about everything in dlib
	// is serializable.  So for example, you can save the learned_pfunct object
	// to disk and recall it later like so:
//	serialize("immersion_result.dat") << learned_pfunct;

	// Now let's open that file back up and load the function object it contains.
//	deserialize("immersion_result.dat") >> learned_pfunct;

	// Note that there is also an example program that comes with dlib called
	// the file_to_code_ex.cpp example.  It is a simple program that takes a
	// file and outputs a piece of C++ code that is able to fully reproduce the
	// file's contents in the form of a std::string object.  So you can use that
	// along with the std::istringstream to save learned decision functions
	// inside your actual C++ code files if you want.  




	// Lastly, note that the decision functions we trained above involved well
	// over 200 basis vectors.  Support vector machines in general tend to find
	// decision functions that involve a lot of basis vectors.  This is
	// significant because the more basis vectors in a decision function, the
	// longer it takes to classify new examples.  So dlib provides the ability
	// to find an approximation to the normal output of a trainer using fewer
	// basis vectors.  

	// Here we determine the cross validation accuracy when we approximate the
	// output using only 10 basis vectors.  To do this we use the reduced2()
	// function.  It takes a trainer object and the number of basis vectors to
	// use and returns a new trainer object that applies the necessary post
	// processing during the creation of decision function objects.
	cout << "\ncross validation accuracy with only 10 support vectors: "
		<< cross_validate_trainer(reduced2(trainer, 10), samples, labels, folds);

	// Let's print out the original cross validation score too for comparison.
	cout << "cross validation accuracy with all the original support vectors: "
		<< cross_validate_trainer(trainer, samples, labels, folds);

	// When you run this program you should see that, for this problem, you can
	// reduce the number of basis vectors down to 10 without hurting the cross
	// validation accuracy. 


	// To get the reduced decision function out we would just do this:
	learned_function.function = reduced2(trainer, 10).train(samples, labels);
	// And similarly for the probabilistic_decision_function: 
	learned_pfunct.function = train_probabilistic_decision_function(reduced2

		(trainer, 10), samples, labels, folds);
	std::getchar();
}
