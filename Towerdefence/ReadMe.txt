INSTALL
-------

Linux
-----

You need the following libraries:
OGRE		http://www.ogre3d.org/
Raknet		http://www.jenkinssoftware.com/
QuickGUI	http://www.ogre3d.org/wiki/index.php/QuickGUI
OIS		http://www.ogre3d.org/

Following assumptions are made about the location of these packages:
-If they registered themself with pkg_config they will be found this way
-Else they should be in /urs/local or /usr

You also need cmake to generate makefiles.

commands:

cmake -G "Unix Makefiles"
make

Windows
-------

Download the windowsSDK package.
Extract it in the main folder of Towerdefence.

cmake -G "Visual Studio xxxx"









