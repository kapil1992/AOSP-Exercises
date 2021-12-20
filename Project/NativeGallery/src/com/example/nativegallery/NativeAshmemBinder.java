package com.example.nativegallery;

public class NativeAshmemBinder {
	public static native void AshmemInit();
	public static native byte[] getImageData();
        static {
		System.loadLibrary("NativeAshmemBinder");
	}
        
	public void ashmemInit() { AshmemInit(); }
	public byte[] getNextImage() { return getImageData(); }
}
