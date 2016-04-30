-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment2
-- ------------------------------------------------------
-- Server version	5.5.44-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `data`
--

DROP TABLE IF EXISTS `data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `data` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `ip` char(30) DEFAULT NULL,
  `username` char(40) DEFAULT NULL,
  `achievementScore` int(11) DEFAULT NULL,
  `socialSCore` int(11) DEFAULT NULL,
  `immersionScore` int(11) DEFAULT NULL,
  `achievementLevel` int(11) DEFAULT NULL,
  `immersionLevel` int(11) DEFAULT NULL,
  `achResult` float DEFAULT NULL,
  `immResult` float DEFAULT NULL,
  `round` mediumint(8) unsigned DEFAULT NULL,
  `seed` bigint(20) DEFAULT NULL,
  `restarts` int(10) unsigned DEFAULT NULL,
  `immersionChoices` tinyint(4) DEFAULT NULL,
  `achievementChoices` tinyint(4) DEFAULT NULL,
  `roundTime` int(10) unsigned DEFAULT NULL,
  `keyboardAPM` int(10) unsigned DEFAULT NULL,
  `mouseAPM` int(10) unsigned DEFAULT NULL,
  `playerDeaths` int(10) unsigned DEFAULT NULL,
  `batDeaths` int(10) unsigned DEFAULT NULL,
  `treesChopped` int(10) unsigned DEFAULT NULL,
  `immersionTime` int(10) unsigned DEFAULT NULL,
  `achievementTime` int(10) unsigned DEFAULT NULL,
  `objectiveCompleted` tinyint(4) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'119.74.77.237, 119.74.77.237','Haha',0,0,0,1,0,1.24451,1.23353,1,1458487437,0,0,0,67,51,32,0,0,0,0,14,1,'2016-03-20 15:25:12'),(2,'119.74.77.237, 119.74.77.237','Haha',0,0,0,2,0,0.95965,0.958259,2,1458487515,0,0,0,83,82,74,0,8,0,0,15,1,'2016-03-20 15:26:44'),(3,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,0,0.269969,0.277813,3,1458487607,0,0,0,73,169,176,0,25,0,0,29,1,'2016-03-20 15:28:07'),(4,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,1,2.50616,2.55985,4,1458487691,0,0,0,92,207,198,0,5,0,25,0,-1,'2016-03-20 15:29:50'),(5,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,2,0.436026,0.455488,5,1458488076,1,0,0,124,315,253,0,0,1,59,0,-1,'2016-03-20 15:36:47'),(6,'220.255.101.225, 220.255.101.2','blacktheon',0,0,0,0,1,4.93681,4.98652,1,1458519118,0,2,0,81,33,39,0,0,0,26,0,-1,'2016-03-21 00:13:24'),(7,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,1,0,0.998368,0.977045,1,1458616980,0,0,1,147,12,10,0,0,0,0,36,1,'2016-03-22 03:25:31'),(8,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,2,0,0.583111,0.57788,2,1458617155,0,2,1,222,27,20,0,16,0,27,17,1,'2016-03-22 03:29:41'),(9,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,2,1,3.71762,3.77524,3,1458617402,0,4,1,316,34,42,0,55,0,47,0,-1,'2016-03-22 03:35:23'),(10,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,3,1,0.404443,0.417956,4,1458617747,0,4,2,91,145,194,0,33,0,0,17,1,'2016-03-22 03:37:24'),(11,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,4,1,-0.361036,-0.499667,5,1458617866,0,6,3,280,73,85,1,16,0,0,47,1,'2016-03-22 03:42:31'),(12,'116.88.78.173, 116.88.78.173','test22',0,0,0,0,1,4.73065,4.77523,1,1458699825,0,0,0,44,42,8,0,0,0,16,0,-1,'2016-03-23 02:24:33'),(13,'167.4.116.130, 167.4.116.130','test22',0,0,0,0,2,4.67189,4.71696,2,1458699888,0,0,0,101,50,15,0,0,1,42,0,-1,'2016-03-23 02:26:31');
/*!40000 ALTER TABLE `data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `surveyResults`
--

DROP TABLE IF EXISTS `surveyResults`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `surveyResults` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `ip` char(30) DEFAULT NULL,
  `username` char(40) DEFAULT NULL,
  `achievementScore` int(11) DEFAULT NULL,
  `socialScore` int(11) DEFAULT NULL,
  `immersionScore` int(11) DEFAULT NULL,
  `achievementLevel` int(11) DEFAULT NULL,
  `immersionLevel` int(11) DEFAULT NULL,
  `question1` tinyint(4) DEFAULT NULL,
  `question2` tinyint(4) DEFAULT NULL,
  `question3` tinyint(4) DEFAULT NULL,
  `question4` tinyint(4) DEFAULT NULL,
  `feedback` char(255) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `surveyResults`
--

LOCK TABLES `surveyResults` WRITE;
/*!40000 ALTER TABLE `surveyResults` DISABLE KEYS */;
INSERT INTO `surveyResults` VALUES (1,'119.74.77.237, 119.74.77.237','C:\\Users\\Benedict\\AppData\\Roaming\\OpenCl',0,0,0,3,2,3,2,2,3,'There\'s this elevator bug. Maybe the character should only interact when on elevator. Yea, the interaction between the character and the environment is good, but sometimes it does interfer too much.','2016-03-20 15:39:09'),(2,'172.26.191.187, 172.26.191.187','C:\\Users\\workshop\\AppData\\Roaming\\OpenCl',0,0,0,4,1,2,3,3,1,'Write feedback here','2016-03-22 03:43:35');
/*!40000 ALTER TABLE `surveyResults` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-03-23 21:12:58
-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment2
-- ------------------------------------------------------
-- Server version	5.5.44-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `data`
--

DROP TABLE IF EXISTS `data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `data` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `ip` char(30) DEFAULT NULL,
  `username` char(40) DEFAULT NULL,
  `achievementScore` int(11) DEFAULT NULL,
  `socialSCore` int(11) DEFAULT NULL,
  `immersionScore` int(11) DEFAULT NULL,
  `achievementLevel` int(11) DEFAULT NULL,
  `immersionLevel` int(11) DEFAULT NULL,
  `achResult` float DEFAULT NULL,
  `immResult` float DEFAULT NULL,
  `round` mediumint(8) unsigned DEFAULT NULL,
  `seed` bigint(20) DEFAULT NULL,
  `restarts` int(10) unsigned DEFAULT NULL,
  `immersionChoices` tinyint(4) DEFAULT NULL,
  `achievementChoices` tinyint(4) DEFAULT NULL,
  `roundTime` int(10) unsigned DEFAULT NULL,
  `keyboardAPM` int(10) unsigned DEFAULT NULL,
  `mouseAPM` int(10) unsigned DEFAULT NULL,
  `playerDeaths` int(10) unsigned DEFAULT NULL,
  `batDeaths` int(10) unsigned DEFAULT NULL,
  `treesChopped` int(10) unsigned DEFAULT NULL,
  `immersionTime` int(10) unsigned DEFAULT NULL,
  `achievementTime` int(10) unsigned DEFAULT NULL,
  `objectiveCompleted` tinyint(4) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'119.74.77.237, 119.74.77.237','Haha',0,0,0,1,0,1.24451,1.23353,1,1458487437,0,0,0,67,51,32,0,0,0,0,14,1,'2016-03-20 15:25:12'),(2,'119.74.77.237, 119.74.77.237','Haha',0,0,0,2,0,0.95965,0.958259,2,1458487515,0,0,0,83,82,74,0,8,0,0,15,1,'2016-03-20 15:26:44'),(3,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,0,0.269969,0.277813,3,1458487607,0,0,0,73,169,176,0,25,0,0,29,1,'2016-03-20 15:28:07'),(4,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,1,2.50616,2.55985,4,1458487691,0,0,0,92,207,198,0,5,0,25,0,-1,'2016-03-20 15:29:50'),(5,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,2,0.436026,0.455488,5,1458488076,1,0,0,124,315,253,0,0,1,59,0,-1,'2016-03-20 15:36:47'),(6,'220.255.101.225, 220.255.101.2','blacktheon',0,0,0,0,1,4.93681,4.98652,1,1458519118,0,2,0,81,33,39,0,0,0,26,0,-1,'2016-03-21 00:13:24'),(7,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,1,0,0.998368,0.977045,1,1458616980,0,0,1,147,12,10,0,0,0,0,36,1,'2016-03-22 03:25:31'),(8,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,2,0,0.583111,0.57788,2,1458617155,0,2,1,222,27,20,0,16,0,27,17,1,'2016-03-22 03:29:41'),(9,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,2,1,3.71762,3.77524,3,1458617402,0,4,1,316,34,42,0,55,0,47,0,-1,'2016-03-22 03:35:23'),(10,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,3,1,0.404443,0.417956,4,1458617747,0,4,2,91,145,194,0,33,0,0,17,1,'2016-03-22 03:37:24'),(11,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,4,1,-0.361036,-0.499667,5,1458617866,0,6,3,280,73,85,1,16,0,0,47,1,'2016-03-22 03:42:31'),(12,'116.88.78.173, 116.88.78.173','test22',0,0,0,0,1,4.73065,4.77523,1,1458699825,0,0,0,44,42,8,0,0,0,16,0,-1,'2016-03-23 02:24:33'),(13,'116.88.78.173, 116.88.78.173','test22',0,0,0,0,2,4.67189,4.71696,2,1458699888,0,0,0,101,50,15,0,0,1,42,0,-1,'2016-03-23 02:26:31'),(14,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,1,0,1.13175,1.13362,1,1458815828,0,0,1,56,90,69,0,0,0,0,10,1,'2016-03-24 10:40:21'),(15,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,2,0,0.814122,0.80596,2,1458815897,0,0,2,67,113,127,0,0,0,0,36,1,'2016-03-24 10:41:40'),(16,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,3,0,-0.123148,-0.104678,3,1458815976,0,0,3,45,222,264,0,50,0,0,21,1,'2016-03-24 10:42:37'),(17,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,4,0,-3.35937,-3.32045,4,1458816033,0,0,4,20,534,717,0,8,0,0,7,1,'2016-03-24 10:43:09'),(18,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,5,0,-0.947805,-0.929123,5,1458816065,0,0,5,42,280,438,0,0,0,0,20,1,'2016-03-24 10:44:03'),(19,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,6,0,-1.63219,-1.79646,6,1458816119,0,0,5,73,207,335,1,3,0,0,15,1,'2016-03-24 10:45:27'),(20,'98.112.153.198, 98.112.153.198','Blade',0,0,0,1,0,0.771411,0.751538,1,1458774174,0,0,1,121,54,16,0,0,0,24,24,1,'2016-03-24 11:07:15'),(21,'98.112.153.198, 98.112.153.198','Blade',0,0,0,2,0,-1.05758,-1.25921,2,1458774309,0,0,2,112,96,117,1,12,0,0,35,1,'2016-03-24 11:09:20'),(22,'98.112.153.198, 98.112.153.198','Blade',0,0,0,2,2,3.19631,3.24688,4,1458774487,0,1,3,105,160,159,0,8,1,36,0,-1,'2016-03-24 11:12:10'),(23,'98.112.153.198, 98.112.153.198','Blade',0,0,0,3,2,-2.04516,-2.00307,5,1458774605,0,2,5,45,417,422,0,58,0,0,16,1,'2016-03-24 11:13:08'),(24,'98.112.153.198, 98.112.153.198','Blade',0,0,0,4,2,-2.87583,-2.78879,6,1458774664,0,2,5,23,840,946,0,0,0,0,10,1,'2016-03-24 11:13:45');
/*!40000 ALTER TABLE `data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `surveyResults`
--

DROP TABLE IF EXISTS `surveyResults`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `surveyResults` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `ip` char(30) DEFAULT NULL,
  `username` char(40) DEFAULT NULL,
  `achievementScore` int(11) DEFAULT NULL,
  `socialScore` int(11) DEFAULT NULL,
  `immersionScore` int(11) DEFAULT NULL,
  `achievementLevel` int(11) DEFAULT NULL,
  `immersionLevel` int(11) DEFAULT NULL,
  `question1` tinyint(4) DEFAULT NULL,
  `question2` tinyint(4) DEFAULT NULL,
  `question3` tinyint(4) DEFAULT NULL,
  `question4` tinyint(4) DEFAULT NULL,
  `feedback` char(255) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `surveyResults`
--

LOCK TABLES `surveyResults` WRITE;
/*!40000 ALTER TABLE `surveyResults` DISABLE KEYS */;
INSERT INTO `surveyResults` VALUES (1,'119.74.77.237, 119.74.77.237','C:\\Users\\Benedict\\AppData\\Roaming\\OpenCl',0,0,0,3,2,3,2,2,3,'There\'s this elevator bug. Maybe the character should only interact when on elevator. Yea, the interaction between the character and the environment is good, but sometimes it does interfer too much.','2016-03-20 15:39:09'),(2,'172.26.191.187, 172.26.191.187','C:\\Users\\workshop\\AppData\\Roaming\\OpenCl',0,0,0,4,1,2,3,3,1,'Write feedback here','2016-03-22 03:43:35'),(3,'14.52.59.60, 14.52.59.60','C:\\Users\\User2\\AppData\\Roaming\\OpenClonk',0,0,0,6,0,4,4,4,2,'a bit too difficult at the end, maybe a tutorial at the start?','2016-03-24 10:46:30'),(4,'98.112.153.198, 98.112.153.198','C:\\Users\\Greenpeace\\AppData\\Roaming\\Open',0,0,0,4,2,4,2,3,3,'Write feedback here','2016-03-24 11:14:02');
/*!40000 ALTER TABLE `surveyResults` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-03-25 16:47:12
-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment2
-- ------------------------------------------------------
-- Server version	5.5.44-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `data`
--

DROP TABLE IF EXISTS `data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `data` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `ip` char(30) DEFAULT NULL,
  `username` char(40) DEFAULT NULL,
  `achievementScore` int(11) DEFAULT NULL,
  `socialSCore` int(11) DEFAULT NULL,
  `immersionScore` int(11) DEFAULT NULL,
  `achievementLevel` int(11) DEFAULT NULL,
  `immersionLevel` int(11) DEFAULT NULL,
  `achResult` float DEFAULT NULL,
  `immResult` float DEFAULT NULL,
  `round` mediumint(8) unsigned DEFAULT NULL,
  `seed` bigint(20) DEFAULT NULL,
  `restarts` int(10) unsigned DEFAULT NULL,
  `immersionChoices` tinyint(4) DEFAULT NULL,
  `achievementChoices` tinyint(4) DEFAULT NULL,
  `roundTime` int(10) unsigned DEFAULT NULL,
  `keyboardAPM` int(10) unsigned DEFAULT NULL,
  `mouseAPM` int(10) unsigned DEFAULT NULL,
  `playerDeaths` int(10) unsigned DEFAULT NULL,
  `batDeaths` int(10) unsigned DEFAULT NULL,
  `treesChopped` int(10) unsigned DEFAULT NULL,
  `immersionTime` int(10) unsigned DEFAULT NULL,
  `achievementTime` int(10) unsigned DEFAULT NULL,
  `objectiveCompleted` tinyint(4) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'119.74.77.237, 119.74.77.237','Haha',0,0,0,1,0,1.24451,1.23353,1,1458487437,0,0,0,67,51,32,0,0,0,0,14,1,'2016-03-20 15:25:12'),(2,'119.74.77.237, 119.74.77.237','Haha',0,0,0,2,0,0.95965,0.958259,2,1458487515,0,0,0,83,82,74,0,8,0,0,15,1,'2016-03-20 15:26:44'),(3,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,0,0.269969,0.277813,3,1458487607,0,0,0,73,169,176,0,25,0,0,29,1,'2016-03-20 15:28:07'),(4,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,1,2.50616,2.55985,4,1458487691,0,0,0,92,207,198,0,5,0,25,0,-1,'2016-03-20 15:29:50'),(5,'119.74.77.237, 119.74.77.237','Haha',0,0,0,3,2,0.436026,0.455488,5,1458488076,1,0,0,124,315,253,0,0,1,59,0,-1,'2016-03-20 15:36:47'),(6,'220.255.101.225, 220.255.101.2','blacktheon',0,0,0,0,1,4.93681,4.98652,1,1458519118,0,2,0,81,33,39,0,0,0,26,0,-1,'2016-03-21 00:13:24'),(7,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,1,0,0.998368,0.977045,1,1458616980,0,0,1,147,12,10,0,0,0,0,36,1,'2016-03-22 03:25:31'),(8,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,2,0,0.583111,0.57788,2,1458617155,0,2,1,222,27,20,0,16,0,27,17,1,'2016-03-22 03:29:41'),(9,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,2,1,3.71762,3.77524,3,1458617402,0,4,1,316,34,42,0,55,0,47,0,-1,'2016-03-22 03:35:23'),(10,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,3,1,0.404443,0.417956,4,1458617747,0,4,2,91,145,194,0,33,0,0,17,1,'2016-03-22 03:37:24'),(11,'172.26.191.187, 172.26.191.187','Aeon',0,0,0,4,1,-0.361036,-0.499667,5,1458617866,0,6,3,280,73,85,1,16,0,0,47,1,'2016-03-22 03:42:31'),(12,'116.88.78.173, 116.88.78.173','test22',0,0,0,0,1,4.73065,4.77523,1,1458699825,0,0,0,44,42,8,0,0,0,16,0,-1,'2016-03-23 02:24:33'),(13,'116.88.78.173, 116.88.78.173','test22',0,0,0,0,2,4.67189,4.71696,2,1458699888,0,0,0,101,50,15,0,0,1,42,0,-1,'2016-03-23 02:26:31'),(14,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,1,0,1.13175,1.13362,1,1458815828,0,0,1,56,90,69,0,0,0,0,10,1,'2016-03-24 10:40:21'),(15,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,2,0,0.814122,0.80596,2,1458815897,0,0,2,67,113,127,0,0,0,0,36,1,'2016-03-24 10:41:40'),(16,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,3,0,-0.123148,-0.104678,3,1458815976,0,0,3,45,222,264,0,50,0,0,21,1,'2016-03-24 10:42:37'),(17,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,4,0,-3.35937,-3.32045,4,1458816033,0,0,4,20,534,717,0,8,0,0,7,1,'2016-03-24 10:43:09'),(18,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,5,0,-0.947805,-0.929123,5,1458816065,0,0,5,42,280,438,0,0,0,0,20,1,'2016-03-24 10:44:03'),(19,'14.52.59.60, 14.52.59.60','PLAYER',0,0,0,6,0,-1.63219,-1.79646,6,1458816119,0,0,5,73,207,335,1,3,0,0,15,1,'2016-03-24 10:45:27'),(20,'98.112.153.198, 98.112.153.198','Blade',0,0,0,1,0,0.771411,0.751538,1,1458774174,0,0,1,121,54,16,0,0,0,24,24,1,'2016-03-24 11:07:15'),(21,'98.112.153.198, 98.112.153.198','Blade',0,0,0,2,0,-1.05758,-1.25921,2,1458774309,0,0,2,112,96,117,1,12,0,0,35,1,'2016-03-24 11:09:20'),(22,'98.112.153.198, 98.112.153.198','Blade',0,0,0,2,2,3.19631,3.24688,4,1458774487,0,1,3,105,160,159,0,8,1,36,0,-1,'2016-03-24 11:12:10'),(23,'98.112.153.198, 98.112.153.198','Blade',0,0,0,3,2,-2.04516,-2.00307,5,1458774605,0,2,5,45,417,422,0,58,0,0,16,1,'2016-03-24 11:13:08'),(24,'98.112.153.198, 98.112.153.198','Blade',0,0,0,4,2,-2.87583,-2.78879,6,1458774664,0,2,5,23,840,946,0,0,0,0,10,1,'2016-03-24 11:13:45'),(25,'121.103.186.37, 121.103.186.37','flash',0,0,0,1,0,1.21448,1.22642,1,1458888435,0,0,1,40,106,112,0,0,0,0,2,1,'2016-03-25 10:26:26'),(26,'121.103.186.37, 121.103.186.37','flash',0,0,0,1,1,3.7653,3.81434,2,1458888487,0,2,1,64,130,102,0,0,0,31,0,-1,'2016-03-25 10:27:42'),(27,'121.103.186.37, 121.103.186.37','flash',0,0,0,1,2,3.98452,4.05312,3,1458888563,0,3,2,91,118,98,0,0,1,10,0,-1,'2016-03-25 10:29:25'),(28,'121.103.186.37, 121.103.186.37','flash',0,0,0,1,3,4.21474,4.29671,4,1458888666,0,4,3,156,97,76,0,0,2,10,0,-1,'2016-03-25 10:32:13'),(29,'121.103.186.37, 121.103.186.37','flash',0,0,0,2,3,-1.33843,-1.28865,5,1458888836,0,4,3,49,369,279,0,0,0,2,3,1,'2016-03-25 10:33:16'),(30,'121.103.186.37, 121.103.186.37','flash',0,0,0,3,3,-0.122511,-0.083015,6,1458888898,0,4,3,101,234,201,0,0,0,0,13,1,'2016-03-25 10:35:11'),(31,'121.103.186.37, 121.103.186.37','player',0,0,0,1,0,1.43086,1.43486,1,1458894194,0,0,1,141,17,13,0,0,0,0,7,1,'2016-03-25 12:04:07'),(32,'121.103.186.37, 121.103.186.37','player',0,0,0,2,0,0.789848,0.786707,2,1458894347,0,0,2,61,122,131,0,0,0,0,30,1,'2016-03-25 12:05:19'),(33,'121.103.186.37, 121.103.186.37','player',0,0,0,3,0,0.656134,0.651405,3,1458894419,0,0,3,117,113,195,0,33,0,0,50,1,'2016-03-25 12:07:27'),(34,'121.103.186.37, 121.103.186.37','player',0,0,0,4,0,-2.07996,-2.06167,4,1458894548,0,0,4,44,361,621,0,37,0,0,21,1,'2016-03-25 12:08:23'),(35,'121.103.186.37, 121.103.186.37','player',0,0,0,5,0,-1.65314,-1.81791,5,1458894605,0,0,5,106,185,314,1,8,0,0,9,1,'2016-03-25 12:10:21'),(36,'121.103.186.37, 121.103.186.37','player',0,0,0,6,0,-1.07058,-1.04709,6,1458894723,0,0,6,81,260,494,0,11,0,0,7,1,'2016-03-25 12:11:55');
/*!40000 ALTER TABLE `data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `surveyResults`
--

DROP TABLE IF EXISTS `surveyResults`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `surveyResults` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `ip` char(30) DEFAULT NULL,
  `username` char(40) DEFAULT NULL,
  `achievementScore` int(11) DEFAULT NULL,
  `socialScore` int(11) DEFAULT NULL,
  `immersionScore` int(11) DEFAULT NULL,
  `achievementLevel` int(11) DEFAULT NULL,
  `immersionLevel` int(11) DEFAULT NULL,
  `question1` tinyint(4) DEFAULT NULL,
  `question2` tinyint(4) DEFAULT NULL,
  `question3` tinyint(4) DEFAULT NULL,
  `question4` tinyint(4) DEFAULT NULL,
  `feedback` char(255) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `surveyResults`
--

LOCK TABLES `surveyResults` WRITE;
/*!40000 ALTER TABLE `surveyResults` DISABLE KEYS */;
INSERT INTO `surveyResults` VALUES (1,'119.74.77.237, 119.74.77.237','C:\\Users\\Benedict\\AppData\\Roaming\\OpenCl',0,0,0,3,2,3,2,2,3,'There\'s this elevator bug. Maybe the character should only interact when on elevator. Yea, the interaction between the character and the environment is good, but sometimes it does interfer too much.','2016-03-20 15:39:09'),(2,'172.26.191.187, 172.26.191.187','C:\\Users\\workshop\\AppData\\Roaming\\OpenCl',0,0,0,4,1,2,3,3,1,'Write feedback here','2016-03-22 03:43:35'),(3,'14.52.59.60, 14.52.59.60','C:\\Users\\User2\\AppData\\Roaming\\OpenClonk',0,0,0,6,0,4,4,4,2,'a bit too difficult at the end, maybe a tutorial at the start?','2016-03-24 10:46:30'),(4,'98.112.153.198, 98.112.153.198','C:\\Users\\Greenpeace\\AppData\\Roaming\\Open',0,0,0,4,2,4,2,3,3,'Write feedback here','2016-03-24 11:14:02'),(5,'121.103.186.37, 121.103.186.37','C:\\Users\\admin\\AppData\\Roaming\\OpenClonk',0,0,0,3,3,4,4,4,4,'fun game! gets boring after a while though','2016-03-25 10:35:55'),(6,'121.103.186.37, 121.103.186.37','C:\\Users\\LuLu\\AppData\\Roaming\\OpenClonk\\',0,0,0,6,0,4,4,3,2,'Write feedback here','2016-03-25 12:12:09');
/*!40000 ALTER TABLE `surveyResults` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-03-25 20:21:57
