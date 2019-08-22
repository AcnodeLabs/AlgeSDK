cd ..
echo git clone https://github.com/erincatto/Box2D.git
echo git clone https://github.com/nats-io/cnats.git
echo git clone https://github.com/ThemsAllTook/libstem_gamepad.git
echo git clone http://github.com/jtsiomb/libdrawtext
git clone -b stable https://github.com/flutter/flutter.git
wget http://dl-ssl.google.com/android/repository/platform-tools_r21-windows.zip
echo please copy platform tools and tools folder to Android SDK_ROOT folder (rename old folders)
echo this step is manual for time bieng and is expected to be automated soon
cd AlgeSDK
Kickstart.bat
