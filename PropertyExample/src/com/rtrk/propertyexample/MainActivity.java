package com.rtrk.propertyexample;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.os.SystemProperties;

public class MainActivity extends Activity {

    private String key = "rtrk.android";
    private String val = "";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        SystemProperties.set(key, "RTRK");
        String property = SystemProperties.get(key, "Another");
        if (!property.equals("RTRK")) {
            SystemProperties.set(key, "RTRK");
        }
        Log.d("PropertyExample", "Property value [ " + property + " ]");
    }

}
