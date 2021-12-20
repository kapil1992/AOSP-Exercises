// IImageDataServer.aidl
package com.example.nativegallery;
// Declare any non-default types here with import statements

import android.os.ParcelFileDescriptor;

interface IImageDataServer {
    void setAshmemFd(in int pfd);
    int requestNextImage();
}
