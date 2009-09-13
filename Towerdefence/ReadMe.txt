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

Next you need to create plugin.cfg in bin/Release and bin/Debug.
Config depends on your system for example:

# Defines plugins to load

# Define plugin folder
PluginFolder=/usr/lib/OGRE

# Define plugins
# Plugin=RenderSystem_Direct3D9_d
Plugin=RenderSystem_GL
Plugin=Plugin_ParticleFX
# Plugin=Plugin_BSPSceneManager
Plugin=Plugin_CgProgramManager
Plugin=libPlugin_PCZSceneManager
Plugin=Plugin_OctreeZone
Plugin=Plugin_OctreeSceneManager

Windows
-------

Download the windowsSDK.zip package (http://argontd.googlecode.com/files/TowerDefenceSDK.zip)
Extract it in the main folder of Towerdefence.

cmake -G "Visual Studio x xxxx"
Open ??.sln and build 









