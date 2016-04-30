-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment4
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
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'172.25.98.64, 172.25.98.64','tao',0,0,0,1,2,3,1458461848,1,6,0,582,54,85,0,12,1,217,0,-1,'2016-03-20 08:29:59'),(2,'172.25.98.64, 172.25.98.64','tao',0,0,0,1,3,4,1458462453,0,8,0,1197,33,45,0,0,2,411,0,-1,'2016-03-20 08:50:18'),(3,'172.27.219.23, 172.27.219.23','Iman',0,0,0,1,0,1,1458528123,0,3,0,473,22,19,0,0,0,8,66,1,'2016-03-21 02:49:56'),(4,'172.27.219.23, 172.27.219.23','Iman',0,0,0,1,1,2,1458528609,0,5,0,154,87,65,0,0,0,55,0,-1,'2016-03-21 02:52:43'),(5,'172.27.219.23, 172.27.219.23','Iman',0,0,0,2,1,3,1458528776,0,8,0,1325,38,18,0,31,2,184,206,1,'2016-03-21 03:15:01'),(6,'172.27.219.23, 172.27.219.23','Iman',0,0,0,3,1,4,1458530114,0,10,1,646,99,52,0,62,2,126,101,1,'2016-03-21 03:26:00'),(7,'172.27.219.23, 172.27.219.23','Iman',0,0,0,4,1,5,1458530773,0,13,1,692,108,59,1,53,2,102,111,1,'2016-03-21 03:37:46'),(8,'172.27.219.23, 172.27.219.23','Iman',0,0,0,5,1,6,1458531478,0,14,1,439,184,109,0,70,0,0,162,1,'2016-03-21 03:45:17'),(9,'172.27.219.23, 172.27.219.23','Iman',0,0,0,6,1,7,1458534639,0,17,1,280,18,18,0,29,0,0,112,1,'2016-03-21 04:35:19'),(10,'172.27.219.23, 172.27.219.23','Iman',0,0,0,7,1,8,1458534929,0,18,1,216,38,44,0,41,0,0,34,1,'2016-03-21 04:39:05'),(11,'172.27.219.23, 172.27.219.23','Iman',0,0,0,8,1,9,1458535155,0,19,1,484,44,33,1,39,0,0,191,1,'2016-03-21 04:47:20'),(12,'172.27.219.23, 172.27.219.23','Iman',0,0,0,9,1,10,1458572834,0,20,1,263,7,8,0,15,0,0,29,1,'2016-03-21 15:11:39'),(13,'172.27.219.23, 172.27.219.23','Iman',0,0,0,10,1,11,1458573108,0,21,1,277,29,35,1,17,0,0,96,1,'2016-03-21 15:16:25'),(14,'172.27.219.23, 172.27.219.23','Iman',0,0,0,11,1,12,1458573395,0,24,1,258,44,54,0,20,0,0,110,1,'2016-03-21 15:20:54'),(15,'172.24.207.48, 172.24.207.48','tao',0,0,0,1,4,5,1458672972,0,8,0,515,25,22,0,0,2,138,0,-1,'2016-03-22 19:07:39'),(16,'172.24.207.48, 172.24.207.48','tao',0,0,0,1,5,6,1458673511,0,8,0,176,116,90,0,0,0,78,0,-1,'2016-03-22 19:10:55'),(17,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,0,1,1,1458726742,0,2,0,184,60,15,0,0,0,53,0,-1,'2016-03-23 09:55:29'),(18,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,1,1,2,1458726951,0,3,0,158,99,38,0,0,0,0,25,1,'2016-03-23 09:58:30'),(19,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,2,1,3,1458727134,0,3,1,71,238,105,0,0,0,0,15,1,'2016-03-23 10:00:07'),(20,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,3,1,4,1458727231,0,3,2,212,120,61,0,58,0,0,117,1,'2016-03-23 10:04:04'),(21,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,4,1,5,1458727467,0,5,3,324,110,63,0,34,0,43,50,1,'2016-03-23 10:09:53'),(22,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,4,2,6,1458727814,0,5,3,210,195,142,0,6,1,35,0,-1,'2016-03-23 10:13:46'),(23,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,5,2,7,1458728048,0,5,4,179,277,272,0,35,0,0,91,1,'2016-03-23 10:17:09');
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
INSERT INTO `surveyResults` VALUES (1,'172.27.219.23, 172.27.219.23','C:\\Users\\Iman Taani\\AppData\\Roaming\\Open',0,0,0,5,1,4,2,4,3,'I didn\'t like the part that i have to kill boss in order to wait for the nect round so I MAYBE will get the right tool .. interesting though !','2016-03-21 03:46:59'),(2,'172.24.207.48, 172.24.207.48','C:\\Users\\Luyu\\AppData\\Roaming\\OpenClonk\\',0,0,0,1,5,2,2,2,2,'Write feedback here','2016-03-22 19:11:39'),(3,'172.25.98.91, 172.25.98.91','C:\\Users\\colon\\AppData\\Roaming\\OpenClonk',0,0,0,5,2,3,2,2,3,'1. Why not both quests? :) (Although it works) 2. Similar to Broforce on Steam, mechanics are similar (although purpose is different) 3. May get repetitive quick in current stt 4. Good music, UI, SFX','2016-03-23 10:20:07');
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

-- Dump completed on 2016-03-23 21:13:09
-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment4
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
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'172.25.98.64, 172.25.98.64','tao',0,0,0,1,2,3,1458461848,1,6,0,582,54,85,0,12,1,217,0,-1,'2016-03-20 08:29:59'),(2,'172.25.98.64, 172.25.98.64','tao',0,0,0,1,3,4,1458462453,0,8,0,1197,33,45,0,0,2,411,0,-1,'2016-03-20 08:50:18'),(3,'172.27.219.23, 172.27.219.23','Iman',0,0,0,1,0,1,1458528123,0,3,0,473,22,19,0,0,0,8,66,1,'2016-03-21 02:49:56'),(4,'172.27.219.23, 172.27.219.23','Iman',0,0,0,1,1,2,1458528609,0,5,0,154,87,65,0,0,0,55,0,-1,'2016-03-21 02:52:43'),(5,'172.27.219.23, 172.27.219.23','Iman',0,0,0,2,1,3,1458528776,0,8,0,1325,38,18,0,31,2,184,206,1,'2016-03-21 03:15:01'),(6,'172.27.219.23, 172.27.219.23','Iman',0,0,0,3,1,4,1458530114,0,10,1,646,99,52,0,62,2,126,101,1,'2016-03-21 03:26:00'),(7,'172.27.219.23, 172.27.219.23','Iman',0,0,0,4,1,5,1458530773,0,13,1,692,108,59,1,53,2,102,111,1,'2016-03-21 03:37:46'),(8,'172.27.219.23, 172.27.219.23','Iman',0,0,0,5,1,6,1458531478,0,14,1,439,184,109,0,70,0,0,162,1,'2016-03-21 03:45:17'),(9,'172.27.219.23, 172.27.219.23','Iman',0,0,0,6,1,7,1458534639,0,17,1,280,18,18,0,29,0,0,112,1,'2016-03-21 04:35:19'),(10,'172.27.219.23, 172.27.219.23','Iman',0,0,0,7,1,8,1458534929,0,18,1,216,38,44,0,41,0,0,34,1,'2016-03-21 04:39:05'),(11,'172.27.219.23, 172.27.219.23','Iman',0,0,0,8,1,9,1458535155,0,19,1,484,44,33,1,39,0,0,191,1,'2016-03-21 04:47:20'),(12,'172.27.219.23, 172.27.219.23','Iman',0,0,0,9,1,10,1458572834,0,20,1,263,7,8,0,15,0,0,29,1,'2016-03-21 15:11:39'),(13,'172.27.219.23, 172.27.219.23','Iman',0,0,0,10,1,11,1458573108,0,21,1,277,29,35,1,17,0,0,96,1,'2016-03-21 15:16:25'),(14,'172.27.219.23, 172.27.219.23','Iman',0,0,0,11,1,12,1458573395,0,24,1,258,44,54,0,20,0,0,110,1,'2016-03-21 15:20:54'),(15,'172.24.207.48, 172.24.207.48','tao',0,0,0,1,4,5,1458672972,0,8,0,515,25,22,0,0,2,138,0,-1,'2016-03-22 19:07:39'),(16,'172.24.207.48, 172.24.207.48','tao',0,0,0,1,5,6,1458673511,0,8,0,176,116,90,0,0,0,78,0,-1,'2016-03-22 19:10:55'),(17,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,0,1,1,1458726742,0,2,0,184,60,15,0,0,0,53,0,-1,'2016-03-23 09:55:29'),(18,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,1,1,2,1458726951,0,3,0,158,99,38,0,0,0,0,25,1,'2016-03-23 09:58:30'),(19,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,2,1,3,1458727134,0,3,1,71,238,105,0,0,0,0,15,1,'2016-03-23 10:00:07'),(20,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,3,1,4,1458727231,0,3,2,212,120,61,0,58,0,0,117,1,'2016-03-23 10:04:04'),(21,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,4,1,5,1458727467,0,5,3,324,110,63,0,34,0,43,50,1,'2016-03-23 10:09:53'),(22,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,4,2,6,1458727814,0,5,3,210,195,142,0,6,1,35,0,-1,'2016-03-23 10:13:46'),(23,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,5,2,7,1458728048,0,5,4,179,277,272,0,35,0,0,91,1,'2016-03-23 10:17:09'),(24,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,1,1,1458814758,0,0,0,48,61,6,0,0,0,11,0,-1,'2016-03-24 10:22:22'),(25,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,2,2,1458814818,0,0,0,109,85,35,0,0,1,25,0,-1,'2016-03-24 10:24:22'),(26,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,3,3,1458814938,0,0,0,172,117,56,0,0,2,27,0,-1,'2016-03-24 10:27:25'),(27,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,4,4,1458815121,0,0,0,254,120,51,0,0,3,68,0,-1,'2016-03-24 10:31:51'),(28,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,5,5,1458815387,0,0,0,67,552,216,0,0,0,35,0,-1,'2016-03-24 10:33:10'),(29,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,6,6,1458815474,0,0,0,34,1141,441,0,0,0,15,0,-1,'2016-03-24 10:34:03'),(30,'112.168.241.70, 112.168.241.70','Theriss',0,0,0,0,1,1,1458820070,0,0,0,128,24,20,0,0,0,75,0,-1,'2016-03-24 11:48:21'),(31,'112.168.241.70, 112.168.241.70','Theriss',0,0,0,1,1,2,1458820210,0,1,0,68,70,53,0,0,0,0,35,1,'2016-03-24 11:49:40'),(32,'112.168.241.70, 112.168.241.70','Theriss',0,0,0,1,2,3,1458820290,0,1,0,76,103,73,0,0,1,25,0,-1,'2016-03-24 11:51:08');
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
INSERT INTO `surveyResults` VALUES (1,'172.27.219.23, 172.27.219.23','C:\\Users\\Iman Taani\\AppData\\Roaming\\Open',0,0,0,5,1,4,2,4,3,'I didn\'t like the part that i have to kill boss in order to wait for the nect round so I MAYBE will get the right tool .. interesting though !','2016-03-21 03:46:59'),(2,'172.24.207.48, 172.24.207.48','C:\\Users\\Luyu\\AppData\\Roaming\\OpenClonk\\',0,0,0,1,5,2,2,2,2,'Write feedback here','2016-03-22 19:11:39'),(3,'172.25.98.91, 172.25.98.91','C:\\Users\\colon\\AppData\\Roaming\\OpenClonk',0,0,0,5,2,3,2,2,3,'1. Why not both quests? :) (Although it works) 2. Similar to Broforce on Steam, mechanics are similar (although purpose is different) 3. May get repetitive quick in current stt 4. Good music, UI, SFX','2016-03-23 10:20:07'),(4,'116.88.78.173, 116.88.78.173','C:\\Users\\JunLong\\AppData\\Roaming\\OpenClo',0,0,0,0,6,3,2,3,1,'Write feedback here','2016-03-24 10:34:24'),(5,'112.168.241.70, 112.168.241.70','C:\\Users\\Theresa\\AppData\\Roaming\\OpenClo',0,0,0,1,2,1,1,2,2,'Write feedback here','2016-03-24 11:51:25');
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

-- Dump completed on 2016-03-25 16:47:19
-- MySQL dump 10.14  Distrib 5.5.44-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: experiment4
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
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES (1,'172.25.98.64, 172.25.98.64','tao',0,0,0,1,2,3,1458461848,1,6,0,582,54,85,0,12,1,217,0,-1,'2016-03-20 08:29:59'),(2,'172.25.98.64, 172.25.98.64','tao',0,0,0,1,3,4,1458462453,0,8,0,1197,33,45,0,0,2,411,0,-1,'2016-03-20 08:50:18'),(3,'172.27.219.23, 172.27.219.23','Iman',0,0,0,1,0,1,1458528123,0,3,0,473,22,19,0,0,0,8,66,1,'2016-03-21 02:49:56'),(4,'172.27.219.23, 172.27.219.23','Iman',0,0,0,1,1,2,1458528609,0,5,0,154,87,65,0,0,0,55,0,-1,'2016-03-21 02:52:43'),(5,'172.27.219.23, 172.27.219.23','Iman',0,0,0,2,1,3,1458528776,0,8,0,1325,38,18,0,31,2,184,206,1,'2016-03-21 03:15:01'),(6,'172.27.219.23, 172.27.219.23','Iman',0,0,0,3,1,4,1458530114,0,10,1,646,99,52,0,62,2,126,101,1,'2016-03-21 03:26:00'),(7,'172.27.219.23, 172.27.219.23','Iman',0,0,0,4,1,5,1458530773,0,13,1,692,108,59,1,53,2,102,111,1,'2016-03-21 03:37:46'),(8,'172.27.219.23, 172.27.219.23','Iman',0,0,0,5,1,6,1458531478,0,14,1,439,184,109,0,70,0,0,162,1,'2016-03-21 03:45:17'),(9,'172.27.219.23, 172.27.219.23','Iman',0,0,0,6,1,7,1458534639,0,17,1,280,18,18,0,29,0,0,112,1,'2016-03-21 04:35:19'),(10,'172.27.219.23, 172.27.219.23','Iman',0,0,0,7,1,8,1458534929,0,18,1,216,38,44,0,41,0,0,34,1,'2016-03-21 04:39:05'),(11,'172.27.219.23, 172.27.219.23','Iman',0,0,0,8,1,9,1458535155,0,19,1,484,44,33,1,39,0,0,191,1,'2016-03-21 04:47:20'),(12,'172.27.219.23, 172.27.219.23','Iman',0,0,0,9,1,10,1458572834,0,20,1,263,7,8,0,15,0,0,29,1,'2016-03-21 15:11:39'),(13,'172.27.219.23, 172.27.219.23','Iman',0,0,0,10,1,11,1458573108,0,21,1,277,29,35,1,17,0,0,96,1,'2016-03-21 15:16:25'),(14,'172.27.219.23, 172.27.219.23','Iman',0,0,0,11,1,12,1458573395,0,24,1,258,44,54,0,20,0,0,110,1,'2016-03-21 15:20:54'),(15,'172.24.207.48, 172.24.207.48','tao',0,0,0,1,4,5,1458672972,0,8,0,515,25,22,0,0,2,138,0,-1,'2016-03-22 19:07:39'),(16,'172.24.207.48, 172.24.207.48','tao',0,0,0,1,5,6,1458673511,0,8,0,176,116,90,0,0,0,78,0,-1,'2016-03-22 19:10:55'),(17,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,0,1,1,1458726742,0,2,0,184,60,15,0,0,0,53,0,-1,'2016-03-23 09:55:29'),(18,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,1,1,2,1458726951,0,3,0,158,99,38,0,0,0,0,25,1,'2016-03-23 09:58:30'),(19,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,2,1,3,1458727134,0,3,1,71,238,105,0,0,0,0,15,1,'2016-03-23 10:00:07'),(20,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,3,1,4,1458727231,0,3,2,212,120,61,0,58,0,0,117,1,'2016-03-23 10:04:04'),(21,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,4,1,5,1458727467,0,5,3,324,110,63,0,34,0,43,50,1,'2016-03-23 10:09:53'),(22,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,4,2,6,1458727814,0,5,3,210,195,142,0,6,1,35,0,-1,'2016-03-23 10:13:46'),(23,'172.25.98.91, 172.25.98.91','BGen_Tan',0,0,0,5,2,7,1458728048,0,5,4,179,277,272,0,35,0,0,91,1,'2016-03-23 10:17:09'),(24,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,1,1,1458814758,0,0,0,48,61,6,0,0,0,11,0,-1,'2016-03-24 10:22:22'),(25,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,2,2,1458814818,0,0,0,109,85,35,0,0,1,25,0,-1,'2016-03-24 10:24:22'),(26,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,3,3,1458814938,0,0,0,172,117,56,0,0,2,27,0,-1,'2016-03-24 10:27:25'),(27,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,4,4,1458815121,0,0,0,254,120,51,0,0,3,68,0,-1,'2016-03-24 10:31:51'),(28,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,5,5,1458815387,0,0,0,67,552,216,0,0,0,35,0,-1,'2016-03-24 10:33:10'),(29,'116.88.78.173, 116.88.78.173','jun',0,0,0,0,6,6,1458815474,0,0,0,34,1141,441,0,0,0,15,0,-1,'2016-03-24 10:34:03'),(30,'112.168.241.70, 112.168.241.70','Theriss',0,0,0,0,1,1,1458820070,0,0,0,128,24,20,0,0,0,75,0,-1,'2016-03-24 11:48:21'),(31,'112.168.241.70, 112.168.241.70','Theriss',0,0,0,1,1,2,1458820210,0,1,0,68,70,53,0,0,0,0,35,1,'2016-03-24 11:49:40'),(32,'112.168.241.70, 112.168.241.70','Theriss',0,0,0,1,2,3,1458820290,0,1,0,76,103,73,0,0,1,25,0,-1,'2016-03-24 11:51:08'),(33,'59.189.184.238, 59.189.184.238','jon',0,0,0,1,0,1,1458900054,0,0,1,36,56,105,0,0,0,0,14,1,'2016-03-25 09:59:51'),(34,'59.189.184.238, 59.189.184.238','jon',0,0,0,2,0,2,1458900102,0,0,2,50,75,170,0,12,0,0,23,1,'2016-03-25 10:00:52'),(35,'59.189.184.238, 59.189.184.238','jon',0,0,0,3,0,3,1458900164,0,0,3,54,96,223,0,16,0,0,22,1,'2016-03-25 10:01:59');
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
INSERT INTO `surveyResults` VALUES (1,'172.27.219.23, 172.27.219.23','C:\\Users\\Iman Taani\\AppData\\Roaming\\Open',0,0,0,5,1,4,2,4,3,'I didn\'t like the part that i have to kill boss in order to wait for the nect round so I MAYBE will get the right tool .. interesting though !','2016-03-21 03:46:59'),(2,'172.24.207.48, 172.24.207.48','C:\\Users\\Luyu\\AppData\\Roaming\\OpenClonk\\',0,0,0,1,5,2,2,2,2,'Write feedback here','2016-03-22 19:11:39'),(3,'172.25.98.91, 172.25.98.91','C:\\Users\\colon\\AppData\\Roaming\\OpenClonk',0,0,0,5,2,3,2,2,3,'1. Why not both quests? :) (Although it works) 2. Similar to Broforce on Steam, mechanics are similar (although purpose is different) 3. May get repetitive quick in current stt 4. Good music, UI, SFX','2016-03-23 10:20:07'),(4,'116.88.78.173, 116.88.78.173','C:\\Users\\JunLong\\AppData\\Roaming\\OpenClo',0,0,0,0,6,3,2,3,1,'Write feedback here','2016-03-24 10:34:24'),(5,'112.168.241.70, 112.168.241.70','C:\\Users\\Theresa\\AppData\\Roaming\\OpenClo',0,0,0,1,2,1,1,2,2,'Write feedback here','2016-03-24 11:51:25'),(6,'59.189.184.238, 59.189.184.238','C:\\Users\\jonathan\\AppData\\Roaming\\OpenCl',0,0,0,3,0,1,2,2,2,'Write feedback here','2016-03-25 10:02:27');
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

-- Dump completed on 2016-03-25 20:22:04
