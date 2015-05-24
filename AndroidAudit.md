### Requirements ###
  1. JDK for building SPADE
  1. Android SDK for working with the emulator, available here: http://developer.android.com/sdk/index.html.

### Setting up the emulator ###
  1. Download Nathaniel's Android ARM emulator with audit enabled from http://www.cs.indiana.edu/~nhusted/project_source/AndroIDSEmulator-GB.tar.gz
  1. Use the `mksdcard` utility from the `android-sdk/tools` directory to create an SD card image with the following command: `mksdcard 32M sdcard.img`
  1. Copy `sdcard.img` to the directory where the Android emulator from step (1) is extracted.
  1. Use `./start.sh` to launch the emulator

### Setting up SPADE ###
  1. Download SPADE using the following command: `svn checkout -r 538 https://data-provenance.googlecode.com/svn/trunk/SPADE/`
  1. Edit the Makefile and change the path on line 5 to point to your `android-sdk/platform-tools` directory
  1. Use `make android-build` to build SPADE.
  1. Use `make android-deploy` to deploy SPADE to the emulator. (The emulator must already be running for this rule to execute successfully.)
  1. Use `make android-kernel` to launch SPADE on the emulator. (From this point on, all activity recorded by the Audit reporter will be stored in `/mnt/sdcard/spade/output/ouput.dot`)

### To stop auditing and retrieve the results ###
  1. Use the `adb` utility (located in `android-sdk/platform-tools`) to start a remote shell in the emulator: `adb shell`
  1. Navigate to `/mnt/sdcard/spade/android-build` and execute: `/system/bin/sh control.sh`. This will launch the Android control client for SPADE.
  1. Execute the following command in the control client to completely terminate SPADE: `shutdown`
  1. Exit from the remote shell and use the following command to pull the Graphviz output of the auditing session: `adb pull /mnt/sdcard/spade/output/output.dot`