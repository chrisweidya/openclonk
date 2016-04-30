-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment3
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
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,0,1,1,1458460788,0,0,0,200,26,7,0,0,0,47,0,-1,'2016-03-20 08:03:33'),(2,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,1,1,2,1458461009,0,0,0,657,40,22,0,187,0,196,95,1,'2016-03-20 08:14:51'),(3,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,2,1,3,1458461688,0,0,0,219,140,75,0,6,0,0,96,1,'2016-03-20 08:18:52'),(4,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,3,1,4,1458461927,0,0,0,86,371,203,0,0,0,0,26,1,'2016-03-20 08:20:38'),(5,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,4,1,5,1458462034,0,0,1,118,290,161,0,6,0,0,30,1,'2016-03-20 08:22:56'),(6,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,0,1,1,1458490541,0,1,0,140,50,21,0,0,0,15,14,-1,'2016-03-20 16:18:06'),(7,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,1,1,2,1458490694,0,3,0,192,85,42,0,75,0,49,23,1,'2016-03-20 16:21:32'),(8,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,2,1,3,1458490899,0,3,1,61,298,162,0,25,0,0,16,1,'2016-03-20 16:22:45'),(9,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,3,1,4,1458490973,0,3,2,110,229,127,0,37,0,0,55,1,'2016-03-20 16:24:47'),(10,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,4,1,5,1458491093,0,3,3,86,335,203,0,21,0,0,26,1,'2016-03-20 16:26:24'),(11,'172.23.20.97, 172.23.20.97','adyang',0,0,0,1,0,1,1458556860,0,0,3,251,44,24,0,75,0,0,84,1,'2016-03-21 10:45:24'),(12,'172.23.20.97, 172.23.20.97','adyang',0,0,0,2,0,2,1458557137,0,0,4,57,225,133,0,6,0,0,13,1,'2016-03-21 10:46:46'),(13,'172.23.20.97, 172.23.20.97','adyang',0,0,0,3,0,3,1458557209,0,0,5,159,120,64,0,12,0,0,55,1,'2016-03-21 10:49:40'),(14,'172.23.20.97, 172.23.20.97','adyang',0,0,0,4,0,4,1458557384,0,0,6,93,263,152,0,12,0,0,40,1,'2016-03-21 10:51:29'),(15,'172.23.20.97, 172.23.20.97','adyang',0,0,0,5,0,5,1458557492,0,0,7,85,323,196,1,0,0,0,2,1,'2016-03-21 10:53:10'),(16,'172.23.20.97, 172.23.20.97','adyang',0,0,0,6,0,6,1458557593,0,0,8,141,234,134,1,4,0,0,48,1,'2016-03-21 10:55:46');
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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `surveyResults`
--

LOCK TABLES `surveyResults` WRITE;
/*!40000 ALTER TABLE `surveyResults` DISABLE KEYS */;
INSERT INTO `surveyResults` VALUES (1,'172.26.186.141, 172.26.186.141','C:\\Users\\Bayan\\AppData\\Roaming\\OpenClonk',0,0,0,4,1,4,2,2,3,'the instructions are in a small font, not very clear to read','2016-03-20 08:24:12'),(2,'116.14.11.116, 116.14.11.116','C:\\Users\\ong19_000\\AppData\\Roaming\\OpenC',0,0,0,4,1,2,3,3,1,'UI needs to be more intuitive; soundtrack is intuitive; graphic configuration is straining on the eyes','2016-03-20 16:29:45'),(3,'172.23.20.97, 172.23.20.97','C:\\Users\\user\\AppData\\Roaming\\OpenClonk\\',0,0,0,6,0,3,1,1,2,'Write feedback here','2016-03-21 10:56:11');
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

-- Dump completed on 2016-03-23 21:13:04
-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment3
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
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,0,1,1,1458460788,0,0,0,200,26,7,0,0,0,47,0,-1,'2016-03-20 08:03:33'),(2,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,1,1,2,1458461009,0,0,0,657,40,22,0,187,0,196,95,1,'2016-03-20 08:14:51'),(3,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,2,1,3,1458461688,0,0,0,219,140,75,0,6,0,0,96,1,'2016-03-20 08:18:52'),(4,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,3,1,4,1458461927,0,0,0,86,371,203,0,0,0,0,26,1,'2016-03-20 08:20:38'),(5,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,4,1,5,1458462034,0,0,1,118,290,161,0,6,0,0,30,1,'2016-03-20 08:22:56'),(6,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,0,1,1,1458490541,0,1,0,140,50,21,0,0,0,15,14,-1,'2016-03-20 16:18:06'),(7,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,1,1,2,1458490694,0,3,0,192,85,42,0,75,0,49,23,1,'2016-03-20 16:21:32'),(8,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,2,1,3,1458490899,0,3,1,61,298,162,0,25,0,0,16,1,'2016-03-20 16:22:45'),(9,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,3,1,4,1458490973,0,3,2,110,229,127,0,37,0,0,55,1,'2016-03-20 16:24:47'),(10,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,4,1,5,1458491093,0,3,3,86,335,203,0,21,0,0,26,1,'2016-03-20 16:26:24'),(11,'172.23.20.97, 172.23.20.97','adyang',0,0,0,1,0,1,1458556860,0,0,3,251,44,24,0,75,0,0,84,1,'2016-03-21 10:45:24'),(12,'172.23.20.97, 172.23.20.97','adyang',0,0,0,2,0,2,1458557137,0,0,4,57,225,133,0,6,0,0,13,1,'2016-03-21 10:46:46'),(13,'172.23.20.97, 172.23.20.97','adyang',0,0,0,3,0,3,1458557209,0,0,5,159,120,64,0,12,0,0,55,1,'2016-03-21 10:49:40'),(14,'172.23.20.97, 172.23.20.97','adyang',0,0,0,4,0,4,1458557384,0,0,6,93,263,152,0,12,0,0,40,1,'2016-03-21 10:51:29'),(15,'172.23.20.97, 172.23.20.97','adyang',0,0,0,5,0,5,1458557492,0,0,7,85,323,196,1,0,0,0,2,1,'2016-03-21 10:53:10'),(16,'172.23.20.97, 172.23.20.97','adyang',0,0,0,6,0,6,1458557593,0,0,8,141,234,134,1,4,0,0,48,1,'2016-03-21 10:55:46'),(17,'42.127.114.65, 42.127.114.65','Umi',0,0,0,1,0,1,1458813813,0,0,1,90,46,22,0,25,0,0,33,1,'2016-03-24 10:07:19'),(18,'42.127.114.65, 42.127.114.65','Umi',0,0,0,1,1,2,1458813950,0,0,2,35,168,94,0,0,0,9,0,-1,'2016-03-24 10:08:42'),(19,'42.127.114.65, 42.127.114.65','Umi',0,0,0,2,1,3,1458813998,0,0,2,60,151,136,0,18,0,0,27,1,'2016-03-24 10:09:54'),(20,'42.127.114.65, 42.127.114.65','Umi',0,0,0,3,1,4,1458814070,0,0,2,72,195,187,0,12,0,11,17,1,'2016-03-24 10:11:18'),(21,'42.127.114.65, 42.127.114.65','Umi',0,0,0,4,1,5,1458814155,0,0,2,82,215,291,1,50,0,0,6,1,'2016-03-24 10:12:53'),(22,'42.127.114.65, 42.127.114.65','Umi',0,0,0,4,2,6,1458814250,0,0,2,123,188,205,0,0,1,61,0,-1,'2016-03-24 10:15:09'),(23,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,0,1,1458774261,0,0,0,53,60,62,0,162,0,0,22,1,'2016-03-24 11:22:36'),(24,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,1,2,1458774329,0,2,0,60,93,72,0,0,0,27,0,-1,'2016-03-24 11:23:50'),(25,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,2,3,1458774402,0,2,0,111,73,51,0,0,1,21,0,-1,'2016-03-24 11:25:53'),(26,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,3,4,1458774525,0,2,0,205,58,35,0,0,2,47,0,-1,'2016-03-24 11:29:32'),(27,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,4,5,1458774745,0,2,0,256,111,49,0,0,2,52,0,-1,'2016-03-24 11:34:02'),(28,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,5,6,1458775015,0,2,0,150,238,106,0,12,0,86,0,-1,'2016-03-24 11:36:46');
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
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `surveyResults`
--

LOCK TABLES `surveyResults` WRITE;
/*!40000 ALTER TABLE `surveyResults` DISABLE KEYS */;
INSERT INTO `surveyResults` VALUES (1,'172.26.186.141, 172.26.186.141','C:\\Users\\Bayan\\AppData\\Roaming\\OpenClonk',0,0,0,4,1,4,2,2,3,'the instructions are in a small font, not very clear to read','2016-03-20 08:24:12'),(2,'116.14.11.116, 116.14.11.116','C:\\Users\\ong19_000\\AppData\\Roaming\\OpenC',0,0,0,4,1,2,3,3,1,'UI needs to be more intuitive; soundtrack is intuitive; graphic configuration is straining on the eyes','2016-03-20 16:29:45'),(3,'172.23.20.97, 172.23.20.97','C:\\Users\\user\\AppData\\Roaming\\OpenClonk\\',0,0,0,6,0,3,1,1,2,'Write feedback here','2016-03-21 10:56:11'),(4,'42.127.114.65, 42.127.114.65','C:\\Users\\BD\\AppData\\Roaming\\OpenClonk\\Um',0,0,0,4,2,2,1,2,2,'Item selection/management can be better','2016-03-24 10:16:01'),(5,'174.107.113.130, 174.107.113.1','C:\\Users\\Acer\\AppData\\Roaming\\OpenClonk\\',0,0,0,1,5,2,1,1,2,'Write feedback here','2016-03-24 11:37:04');
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

-- Dump completed on 2016-03-25 16:47:16
-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment3
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
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,0,1,1,1458460788,0,0,0,200,26,7,0,0,0,47,0,-1,'2016-03-20 08:03:33'),(2,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,1,1,2,1458461009,0,0,0,657,40,22,0,187,0,196,95,1,'2016-03-20 08:14:51'),(3,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,2,1,3,1458461688,0,0,0,219,140,75,0,6,0,0,96,1,'2016-03-20 08:18:52'),(4,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,3,1,4,1458461927,0,0,0,86,371,203,0,0,0,0,26,1,'2016-03-20 08:20:38'),(5,'172.26.186.141, 172.26.186.141','Bayan',0,0,0,4,1,5,1458462034,0,0,1,118,290,161,0,6,0,0,30,1,'2016-03-20 08:22:56'),(6,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,0,1,1,1458490541,0,1,0,140,50,21,0,0,0,15,14,-1,'2016-03-20 16:18:06'),(7,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,1,1,2,1458490694,0,3,0,192,85,42,0,75,0,49,23,1,'2016-03-20 16:21:32'),(8,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,2,1,3,1458490899,0,3,1,61,298,162,0,25,0,0,16,1,'2016-03-20 16:22:45'),(9,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,3,1,4,1458490973,0,3,2,110,229,127,0,37,0,0,55,1,'2016-03-20 16:24:47'),(10,'116.14.11.116, 116.14.11.116','Alfred',0,0,0,4,1,5,1458491093,0,3,3,86,335,203,0,21,0,0,26,1,'2016-03-20 16:26:24'),(11,'172.23.20.97, 172.23.20.97','adyang',0,0,0,1,0,1,1458556860,0,0,3,251,44,24,0,75,0,0,84,1,'2016-03-21 10:45:24'),(12,'172.23.20.97, 172.23.20.97','adyang',0,0,0,2,0,2,1458557137,0,0,4,57,225,133,0,6,0,0,13,1,'2016-03-21 10:46:46'),(13,'172.23.20.97, 172.23.20.97','adyang',0,0,0,3,0,3,1458557209,0,0,5,159,120,64,0,12,0,0,55,1,'2016-03-21 10:49:40'),(14,'172.23.20.97, 172.23.20.97','adyang',0,0,0,4,0,4,1458557384,0,0,6,93,263,152,0,12,0,0,40,1,'2016-03-21 10:51:29'),(15,'172.23.20.97, 172.23.20.97','adyang',0,0,0,5,0,5,1458557492,0,0,7,85,323,196,1,0,0,0,2,1,'2016-03-21 10:53:10'),(16,'172.23.20.97, 172.23.20.97','adyang',0,0,0,6,0,6,1458557593,0,0,8,141,234,134,1,4,0,0,48,1,'2016-03-21 10:55:46'),(17,'42.127.114.65, 42.127.114.65','Umi',0,0,0,1,0,1,1458813813,0,0,1,90,46,22,0,25,0,0,33,1,'2016-03-24 10:07:19'),(18,'42.127.114.65, 42.127.114.65','Umi',0,0,0,1,1,2,1458813950,0,0,2,35,168,94,0,0,0,9,0,-1,'2016-03-24 10:08:42'),(19,'42.127.114.65, 42.127.114.65','Umi',0,0,0,2,1,3,1458813998,0,0,2,60,151,136,0,18,0,0,27,1,'2016-03-24 10:09:54'),(20,'42.127.114.65, 42.127.114.65','Umi',0,0,0,3,1,4,1458814070,0,0,2,72,195,187,0,12,0,11,17,1,'2016-03-24 10:11:18'),(21,'42.127.114.65, 42.127.114.65','Umi',0,0,0,4,1,5,1458814155,0,0,2,82,215,291,1,50,0,0,6,1,'2016-03-24 10:12:53'),(22,'42.127.114.65, 42.127.114.65','Umi',0,0,0,4,2,6,1458814250,0,0,2,123,188,205,0,0,1,61,0,-1,'2016-03-24 10:15:09'),(23,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,0,1,1458774261,0,0,0,53,60,62,0,162,0,0,22,1,'2016-03-24 11:22:36'),(24,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,1,2,1458774329,0,2,0,60,93,72,0,0,0,27,0,-1,'2016-03-24 11:23:50'),(25,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,2,3,1458774402,0,2,0,111,73,51,0,0,1,21,0,-1,'2016-03-24 11:25:53'),(26,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,3,4,1458774525,0,2,0,205,58,35,0,0,2,47,0,-1,'2016-03-24 11:29:32'),(27,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,4,5,1458774745,0,2,0,256,111,49,0,0,2,52,0,-1,'2016-03-24 11:34:02'),(28,'174.107.113.130, 174.107.113.1','pollock84',0,0,0,1,5,6,1458775015,0,2,0,150,238,106,0,12,0,86,0,-1,'2016-03-24 11:36:46'),(29,'77.222.189.143, 77.222.189.143','Eliminator',0,0,0,0,2,2,1458912616,0,2,0,61,44,23,0,0,1,12,0,-1,'2016-03-25 10:09:48'),(30,'77.222.189.143, 77.222.189.143','Eliminator',0,0,0,1,2,3,1458912691,0,2,0,64,90,45,0,25,0,0,34,1,'2016-03-25 10:11:06'),(31,'77.222.189.143, 77.222.189.143','Eliminator',0,0,0,2,2,4,1458912769,0,2,1,52,144,150,0,43,0,0,25,1,'2016-03-25 10:12:13'),(32,'77.222.189.143, 77.222.189.143','Eliminator',0,0,0,3,2,5,1458912836,0,2,2,46,211,199,0,4,0,0,21,1,'2016-03-25 10:13:12'),(33,'77.222.189.143, 77.222.189.143','Eliminator',0,0,0,4,2,6,1458912895,0,2,3,81,152,213,0,12,0,0,40,1,'2016-03-25 10:14:48');
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
INSERT INTO `surveyResults` VALUES (1,'172.26.186.141, 172.26.186.141','C:\\Users\\Bayan\\AppData\\Roaming\\OpenClonk',0,0,0,4,1,4,2,2,3,'the instructions are in a small font, not very clear to read','2016-03-20 08:24:12'),(2,'116.14.11.116, 116.14.11.116','C:\\Users\\ong19_000\\AppData\\Roaming\\OpenC',0,0,0,4,1,2,3,3,1,'UI needs to be more intuitive; soundtrack is intuitive; graphic configuration is straining on the eyes','2016-03-20 16:29:45'),(3,'172.23.20.97, 172.23.20.97','C:\\Users\\user\\AppData\\Roaming\\OpenClonk\\',0,0,0,6,0,3,1,1,2,'Write feedback here','2016-03-21 10:56:11'),(4,'42.127.114.65, 42.127.114.65','C:\\Users\\BD\\AppData\\Roaming\\OpenClonk\\Um',0,0,0,4,2,2,1,2,2,'Item selection/management can be better','2016-03-24 10:16:01'),(5,'174.107.113.130, 174.107.113.1','C:\\Users\\Acer\\AppData\\Roaming\\OpenClonk\\',0,0,0,1,5,2,1,1,2,'Write feedback here','2016-03-24 11:37:04'),(6,'77.222.189.143, 77.222.189.143','C:\\Users\\Kevin92\\AppData\\Roaming\\OpenClo',0,0,0,4,2,2,3,1,2,'no comments','2016-03-25 10:15:12');
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

-- Dump completed on 2016-03-25 20:22:01
