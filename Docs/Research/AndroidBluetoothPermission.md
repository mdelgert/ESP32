
# Documenting Required Bluetooth Permission Changes for Android 12+ in MAUI

This document outlines the necessary changes to enable Bluetooth functionality in a .NET MAUI application for Android 12 and higher.

---

## Changes Made in `AndroidManifest.xml`

The following permissions were added to the `AndroidManifest.xml` file:

```xml
<uses-permission android:name="android.permission.BLUETOOTH" android:maxSdkVersion="30" />
<uses-permission android:name="android.permission.BLUETOOTH_ADMIN" android:maxSdkVersion="30" />
<uses-permission android:name="android.permission.BLUETOOTH_SCAN" android:usesPermissionFlags="neverForLocation" />
<uses-permission android:name="android.permission.BLUETOOTH_CONNECT" />
<uses-permission android:name="android.permission.BLUETOOTH_ADVERTISE" />
```

### Explanation of Changes:
1. **Support for Legacy Devices (API Levels 30 and Below):**
   - `BLUETOOTH` and `BLUETOOTH_ADMIN` permissions are required for devices running Android 11 or earlier.
   - These permissions were restricted to API level 30 and below using the `android:maxSdkVersion` attribute.

2. **Granular Permissions for Android 12+ (API Level 31 and Above):**
   - **`BLUETOOTH_SCAN`**: Required for scanning Bluetooth devices.
     - Added `android:usesPermissionFlags="neverForLocation"` to clarify it is not used for location tracking.
   - **`BLUETOOTH_CONNECT`**: Required for connecting to Bluetooth devices.
   - **`BLUETOOTH_ADVERTISE`**: Required for advertising as a Bluetooth device.

3. **Backward Compatibility:**
   - Ensures that permissions are correctly applied for both older and newer versions of Android.

---

## Why No Runtime Permission Handling Was Needed

### Normal vs. Dangerous Permissions:
- **Normal Permissions**: 
  - Permissions like `BLUETOOTH_SCAN`, `BLUETOOTH_CONNECT`, and `BLUETOOTH_ADVERTISE` are automatically granted at install time.
  - These permissions do not require runtime prompts.
  
- **Dangerous Permissions**: 
  - Permissions like `ACCESS_FINE_LOCATION` require runtime prompts.
  - Since Bluetooth functionality in this app does not involve location data, no dangerous permissions were needed.

### Implications:
- The app automatically receives the declared Bluetooth permissions without requiring additional runtime permission requests.

---

## Key Takeaways
1. **Declare All Necessary Permissions in `AndroidManifest.xml`:**
   - Ensure all required permissions are added explicitly, with the appropriate API level constraints.

2. **Avoid Unnecessary Runtime Permission Code:**
   - Runtime permission requests are only needed for dangerous permissions.
   - Adding unnecessary runtime permission handling code may lead to confusion and unintended behavior.

3. **Validate the Permissions at Build Time:**
   - Use the **Merged Manifest** in Visual Studio to confirm that the permissions are included in the final manifest.

---

## Further Reading
- [Android Bluetooth Permissions Documentation](https://developer.android.com/guide/topics/connectivity/bluetooth/permissions)
- [MAUI Documentation](https://learn.microsoft.com/en-us/dotnet/maui/)

---

## Example Final `AndroidManifest.xml`
```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.example.myapp">
    
    <uses-permission android:name="android.permission.BLUETOOTH" android:maxSdkVersion="30" />
    <uses-permission android:name="android.permission.BLUETOOTH_ADMIN" android:maxSdkVersion="30" />
    <uses-permission android:name="android.permission.BLUETOOTH_SCAN" android:usesPermissionFlags="neverForLocation" />
    <uses-permission android:name="android.permission.BLUETOOTH_CONNECT" />
    <uses-permission android:name="android.permission.BLUETOOTH_ADVERTISE" />

    <application android:label="MyApp" android:theme="@style/Maui.SplashTheme">
        <!-- Application-specific settings -->
    </application>
</manifest>
```

## Additional Required Code for MainActivity

The following code is required to handle Bluetooth permissions at runtime for Android 12 and higher.

Place this in the `MainActivity.cs` file of your MAUI application:

```csharp
using Android;
using Android.App;
using Android.Content.PM;
using Android.OS;

namespace PassTxt.HybridApp
{
    [Activity(
        Theme = "@style/Maui.SplashTheme", 
        MainLauncher = true, 
        ConfigurationChanges = ConfigChanges.ScreenSize 
                              | ConfigChanges.Orientation 
                              | ConfigChanges.UiMode 
                              | ConfigChanges.ScreenLayout 
                              | ConfigChanges.SmallestScreenSize 
                              | ConfigChanges.Density)]
    public class MainActivity : MauiAppCompatActivity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Request Bluetooth permissions for Android 12 and above
            if (Build.VERSION.SdkInt >= BuildVersionCodes.S)
            {
                RequestBluetoothPermissions();
            }
        }

        private void RequestBluetoothPermissions()
        {
            // Define the required permissions
            string[] permissions = new string[]
            {
                Manifest.Permission.BluetoothScan,
                Manifest.Permission.BluetoothConnect,
                Manifest.Permission.BluetoothAdvertise
            };

            // Check if permissions are already granted
            if (!HasPermissions(permissions))
            {
                // Request permissions if not granted
                RequestPermissions(permissions, 1001);
            }
        }

        private bool HasPermissions(string[] permissions)
        {
            // Check each permission to see if it's granted
            foreach (var permission in permissions)
            {
                if (CheckSelfPermission(permission) != Permission.Granted)
                    return false;
            }
            return true;
        }

        public override void OnRequestPermissionsResult(int requestCode, string[] permissions, Permission[] grantResults)
        {
            base.OnRequestPermissionsResult(requestCode, permissions, grantResults);

            if (requestCode == 1001)
            {
                // Handle the result of the permission request
                for (int i = 0; i < permissions.Length; i++)
                {
                    if (grantResults[i] != Permission.Granted)
                    {
                        // Permission denied; show a message to the user
                        Android.Widget.Toast.MakeText(
                            this, 
                            $"{permissions[i]} denied. Bluetooth features may not work.", 
                            Android.Widget.ToastLength.Long).Show();
                    }
                }
            }
        }
    }
}
```

### Purpose of this Code
1. Ensures that Bluetooth permissions (`BLUETOOTH_SCAN`, `BLUETOOTH_CONNECT`, `BLUETOOTH_ADVERTISE`) are requested at runtime for Android 12 and higher.
2. Handles cases where users may deny permissions, and gracefully informs them that certain features may not work.

Add this code to your `MainActivity.cs` file, and combine it with the changes in the `AndroidManifest.xml` for complete Bluetooth functionality.


---

## Useful Links

- [MAUI Android Manifest Documentation](https://learn.microsoft.com/en-us/dotnet/maui/android/manifest?view=net-maui-9.0)

This link provides more details on how to configure and work with the `AndroidManifest.xml` in a .NET MAUI project.

