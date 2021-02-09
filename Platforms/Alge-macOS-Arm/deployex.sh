security unlock-keychain login.keychain
dir_rel=`xcodebuild -showBuildSettings | grep TARGET_BUILD_DIR | cut -c24-`
name_app=`xcodebuild -showBuildSettings | grep 'WRAPPER_NAME' | cut -c20-`
dir_dbg=${dir_rel/Release/Debug}
sch=`xcodebuild -list -project Alge-macOS-Arm.xcodeproj/ | grep '     '`
schemeName="${sch##* }"
xcodebuild -scheme $schemeName build
cp -v *.dylib $dir_dbg/$name_app/Contents/MacOS
echo $dir_dbg/$name_app
