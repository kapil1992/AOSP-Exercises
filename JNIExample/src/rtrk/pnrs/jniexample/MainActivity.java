package rtrk.pnrs.jniexample;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


public class MainActivity extends Activity implements View.OnClickListener {

    private static final int INVALID_NUMBER = -1;

    private Button cCalculate;
    private EditText cInput;
    private TextView cResult;
    private FibonacciNative cFibLib;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        cInput = (EditText) findViewById(R.id.input_number);
        cCalculate = (Button) findViewById(R.id.action_calculate);
        cResult = (TextView) findViewById(R.id.result);

        cCalculate.setOnClickListener(this);
        
        cFibLib = new FibonacciNative();
    }

    @Override
    public void onClick(View pView) {
        switch (pView.getId()) {
            case R.id.action_calculate:
                int mNumber = INVALID_NUMBER;

                try {
                    mNumber = Integer.parseInt(cInput.getText().toString());
                } catch (NumberFormatException pNFE) {
                    Toast.makeText(getApplicationContext(), pNFE.toString(), Toast.LENGTH_LONG).show();
                }
                if (mNumber == INVALID_NUMBER) {
                    return;
                }
                long mRet = cFibLib.get(mNumber);
                cResult.setText(getResources().getString(R.string.str_result) + mRet);
                break;
        }
    }
}
