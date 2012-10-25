package com.squareup.tape.native_;

import com.squareup.tape.QueueFile;
import com.squareup.tape.QueueFile.ElementReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.lang.String;
import java.lang.System;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

/*-[
  // Header for objectiveC code generated by j2objC
  #include "queuefile.h"
]-*/

public class QueueFileNative implements QueueFile {
  ByteBuffer nativeObj;

  /**
   * Make SURE you call close() on every object, otherwise the native code will not free
   * associated resources (memory and file handle).
   * @param filename
   * @throws IOException
   */
  public QueueFileNative(String filename) throws IOException {
    nativeObj = nativeNew(filename);
  }

  private native ByteBuffer nativeNew(String filename) /*-[
    // objC code here
  ]-*/;

  public native int getFileLength() /*-[
    // objC code here
  ]-*/;

  public native void add(byte[] data) throws IOException /*-[
    // objC code here
  ]-*/;

  public native void add(byte[] data, int offset, int count) throws IOException /*-[
    // objC code here
  ]-*/;

  public native boolean isEmpty() /*-[
    // objC code here
  ]-*/;

  public native byte[] peek() throws IOException /*-[
    // objC code here
  ]-*/;

  public native void peek(ElementReader reader) throws IOException /*-[
    // objC code here
  ]-*/;

  public native void forEach(ElementReader reader) throws IOException /*-[
    // objC code here
  ]-*/;

  public native int size() /*-[
    // objC code here
  ]-*/;

  public native void remove() throws IOException /*-[
    // objC code here
  ]-*/;

  public native void clear() throws IOException /*-[
    // objC code here
  ]-*/;

  public native void close() throws IOException /*-[
    // objC code here
  ]-*/;

  public native String toString() /*-[
    // objC code here
  ]-*/;

  static {
      System.loadLibrary("c-tape-android");
  }
}
