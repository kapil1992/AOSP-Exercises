package com.example.nativegallery;

import android.app.Activity;

import android.os.Bundle;
import android.os.IBinder;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.os.ServiceManager;
import android.os.RemoteException;
import android.util.Log;
import com.example.nativegallery.IImageDataServer;
import android.graphics.BitmapFactory;
import android.os.ParcelFileDescriptor;
import java.io.FileDescriptor;
import android.os.MemoryFile;
import java.util.Arrays;
import java.io.ByteArrayOutputStream;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.util.Base64;

public class MainActivity extends Activity {

    Button imgBtn;
    ImageView imageView;
    IImageDataServer imageDataServer;
    NativeAshmemBinder nab;
    public static final String TAG = "Nativegallary";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        /*IBinder binder = (IBinder) ServiceManager.getService("ImageDataServer");
        imageDataServer = IImageDataServer.Stub.asInterface(binder);*/
        imgBtn = (Button) findViewById(R.id.bt_next_img);
        imageView = (ImageView) findViewById(R.id.iv_gallary);
        imageView.setImageResource(R.drawable.ic_launcher);
	nab =  new NativeAshmemBinder();
        nab.ashmemInit();
        imgBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
		Log.d(TAG, "OnCLicked");
		try {
			 byte[] imgData = nab.getNextImage();
			 Log.d(TAG, "ImageData : " + Arrays.toString(imgData));
			 Bitmap bmp = BitmapFactory.decodeByteArray(imgData, 0, imgData.length);
			 Log.d(TAG, "ImageDataLength : " + imgData.length + " bmp = " + bmp);
			 imageView.setImageBitmap(bmp);
			 //imageView.setImageBitmap(BitmapFactory.decodeResource(getResources(), R.drawable.image1));
		} catch (Exception e) {
			e.printStackTrace();
		}	
            }
        });
    }

    // convert from bitmap to byte array
    public byte[] getBytesFromBitmap(Bitmap bitmap) {
    	ByteArrayOutputStream stream = new ByteArrayOutputStream();
    	bitmap.compress(CompressFormat.JPEG, 70, stream);
    	return stream.toByteArray();
    }


    /*private void AshmemInit() {
        try {
		MemoryFile mf  = new MemoryFile("java-ashmem-region", 8*1024);
		Log.d(TAG, "Length of Ashmeme = " + mf.length());
		FileDescriptor fd = mf.getFileDescriptor(); 
 
		ParcelFileDescriptor pfd = ParcelFileDescriptor.dup(fd);
		Log.d(TAG, "filedescriptor = " + pfd);
		imageDataServer.setAshmemFd(pfd.getFd());
        } catch (Exception e) { e.printStackTrace(); }
    }*/

    /*private FileDescriptor getFileDescriptor() {
        try {
		int ashmemfd = imageDataServer.getAshmemFd();
		ParcelFileDescriptor pfd = ParcelFileDescriptor.fromFd(ashmemfd);
		Log.d(TAG, "ashmemFd = "+ashmemfd);
	        javaFd = pfd.getFileDescriptor();
		return javaFd;	
	} catch (Exception e) { e.printStackTrace(); }
	return null;
    }*/
}
