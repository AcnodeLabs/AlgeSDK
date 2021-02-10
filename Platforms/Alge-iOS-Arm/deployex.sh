security unlock-keychain login.keychain
dir_rel=`xcodebuild -showBuildSettings | grep TARGET_BUILD_DIR | cut -c24-`
name_app=`xcodebuild -showBuildSettings | grep 'EXECUTABLE_FOLDER_PATH' | cut -c30-`
dir_dbg=${dir_rel/Release/Debug}
sch=`xcodebuild -list -project Alge-iOS-Arm.xcodeproj/ | grep '     '`
schemeName="${sch##* }"
xcodebuild -scheme $schemeName build
ios-deploy --debug --bundle $dir_dbg/$name_app
