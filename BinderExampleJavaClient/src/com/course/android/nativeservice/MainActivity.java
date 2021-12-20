package com.course.android.nativeservice;

import android.app.Activity;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;
import com.course.android.nativeservice.IExample;

public class MainActivity extends Activity {

    public static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        testNativeService();
    }

    private void testNativeService() {
        IBinder binder = (IBinder) ServiceManager.getService("Example"); 
	IExample example = IExample.Stub.asInterface(binder); 
	try { 
                example.setExample(15);
    		int value = example.getExample(); 
    		Log.d(TAG, "value = " + value); 
	} catch (RemoteException e) { 
    		Log.d(TAG, "getExample FAILED"); 
	}
    }
}
