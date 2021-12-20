package rtrk.pnrs.anr;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;


public class ANRExample extends Activity implements OnClickListener {
    
    private Button bSleep, bCrach;
    
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layout_hello_jni);
        bSleep = (Button)findViewById(R.id.btnSleep);
        bSleep.setOnClickListener(this);
        bCrach = (Button)findViewById(R.id.btnCrash);
        bCrach.setOnClickListener(this);
    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnSleep:
                anrSleep();
                break;
            case R.id.btnCrash:
                anrCrash();
                break;
        }
    }

    static {
        System.loadLibrary("anrjni");
    }

    public native void anrSleep();
    public native int anrCrash();
}
