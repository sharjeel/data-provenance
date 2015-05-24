# SPADE for Android #

This page will guide you through setting up SPADE for use with Android.

## Requirements ##

Please ensure that you have the following installed on your system:

  * `gcc`
  * `make`
  * `subversion`
  * [Oracle JDK](http://www.oracle.com/technetwork/java/javase/downloads/index.html)
  * Android SDK
  * Graphviz

## Setting up Android SDK ##

Download the Android SDK:

  * For Mac OS X, [click here](http://dl.google.com/android/android-sdk_r22.0.5-macosx.zip).
  * For Linux, [click here](http://dl.google.com/android/android-sdk_r22.0.5-linux.tgz).

Once the download is complete, extract the archive. This will create a new directory containing the Android SDK. On Mac OS X, this directory will be `android-sdk-macosx`. On Linux, it will be `android-sdk-linux`. We will assume `$ANDROID_SDK` is set to this directory. In the terminal window, navigate to this directory and run `./tools/android`:
```
cd $ANDROID_SDK
./tools/android
```
This will open a new window showing the list of packages available for download via the Android SDK. The `Android SDK Tools, Android SDK Platform-tools, Android SDK Build-tools`, and `SDK Platform` for the target version should be selected for installation, and click the `Install ... packages` button. After exiting, run `tools/android` again and select the `ARM EABI System Image` for installation.

Once the installation is complete, new directories will have been created in the Android SDK directory. These need to be added to the shell path. For a `bash` shell, this can be done appending the following line to the end of `~/.profile`:
```
export PATH=$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools:$ANDROID_SDK/build-tools/19.1.0:$PATH
```
(Note: above `19.1.0` needs to be replaced with the appropriate directory name. `19.1.0` is the directory on Android 4.4.2 (API 19).)

An Android Virtual Device (AVD) is an emulator version that lets you run Android on your computer without the need for an actual Android device. In the next step, create an AVD by executing the following command:
```
android create avd -n SPADE_AVD -t "android-19" -c 100M
```
(Note: `android-19` should be replaced by the API version corresponding to the Android installed.)

When prompted to create a custom hardware profile, just press the `Enter` key to select the default hardware configuration. This will create an AVD named `SPADE_AVD` with a memory card that has a 100 MB capacity.

## Setting up SPADE ##

Check out SPADE from the source code repository by executing the following command in the terminal window:
```
svn checkout http://data-provenance.googlecode.com/svn/trunk/SPADE/
```
This command will create a new `SPADE` directory and download the required files into it. To compile the SPADE code, navigate to this newly created directory and configure the package before executing the `make` command as follows:
```
cd SPADE
./configure
make android-build
```

## Starting the Android emulator and running SPADE ##

The Android AVD that was created earlier can be launched in the emulator by executing the following:
```
emulator -avd SPADE_AVD -wipe-data &
```
Once the emulator is started, SPADE can be launched in it by running the following command from the SPADE directory:
```
make android-start &
```
To stop SPADE, execute the following:
```
make android-stop
```
SPADE will capture provenance activity on the device from the moment it is started to the point at which it is stopped. To extract the provenance graph file that was generated for the activity during this period, use the following command:
```
adb pull /sdcard/spade/audit.dot
```
Using Graphviz, this file can be converted to an image for viewing:
```
dot -T svg -o audit.svg audit.dot
```