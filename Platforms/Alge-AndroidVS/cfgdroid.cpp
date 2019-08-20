#include <iostream>
#include <string>

using namespace std;

void ln(string line) {
cout << line << "\n";
}

string package = "com.acnodelabs.alge.PoppingTime";
string appname = "PoppingTime";
string version = "1";
string sdkver = "16";
string orientation = "landscape";

int main(int argc, char *argv[])
{
if (argc<6) {
    cout << "required arguments: package appname ver sdkver orientation\n";
    return -1;
}
 package = string(argv[1]);
 appname = string(argv[2]);
 version = string(argv[3]);
 sdkver = string(argv[4]);
 orientation = string(argv[5]);

ln("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
ln("<manifest xmlns:android=\"http://schemas.android.com/apk/res/android\" android:versionCode=\""+version+"\" android:versionName=\""+version+ "\" package=\"" + package + "\">");
ln("<uses-sdk android:minSdkVersion=\""+sdkver+"\" />");
ln("<application  android:theme=\"@style/android:Theme.Black.NoTitleBar\" android:label=\""+appname+"\" android:debuggable=\"false\" android:icon=\"@drawable/icon\">");
ln("<activity android:label=\""+appname+"\" android:screenOrientation=\""+orientation+"\" android:name=\""+appname+"\">");
ln("<intent-filter>");
ln("<action android:name=\"android.intent.action.MAIN\" />");
ln("<category android:name=\"android.intent.category.LAUNCHER\" />");
ln("</intent-filter>");
ln("</activity>");
ln("<activity android:name=\"com.paypal.android.MEP.PayPalActivity\" android:theme=\"@android:style/Theme.Translucent.NoTitleBar\" android:configChanges=\"keyboardHidden|orientation\"/><!-- The application's publisher ID assigned by AdMob --><meta-data android:value=\"a14d6546c142771\" android:name=\"ADMOB_PUBLISHER_ID\" /><!-- AdMobActivity definition --><activity android:name=\"com.admob.android.ads.AdMobActivity\" android:theme=\"@android:style/Theme.NoTitleBar.Fullscreen\" android:configChanges=\"orientation|keyboard|keyboardHidden\" /><!-- Track Market installs --><receiver android:name=\"com.admob.android.ads.analytics.InstallReceiver\" android:exported=\"true\"><intent-filter> <action android:name=\"com.android.vending.INSTALL_REFERRER\" /></intent-filter> </receiver></application>");
ln("<uses-permission android:name=\"android.permission.INTERNET\"/> <uses-permission android:name=\"android.permission.READ_PHONE_STATE\"/>");
ln("</manifest>");
    return 0;
}