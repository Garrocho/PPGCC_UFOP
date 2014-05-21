package com.cgphotoedit;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnTouchListener;

public class PaintSurfaceView extends SurfaceView implements Runnable, OnTouchListener{
	// Surface holder allows to control and monitor the surface
    private SurfaceHolder mHolder;
 
    // A thread where the painting activities are taking place
    private Thread mThread;
 
    // A flag which controls the start and stop of the repainting of the SurfaceView
    private boolean mFlag = false;
 
    // X coordinate of the touched position
    private float mX;
 
    // Y Coordinate of the touched position
    private float mY;
 
    // Paint
    private Paint mPaint;
    
    public PaintSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
 
        // Getting the holder
        mHolder = getHolder();
 
        // Initializing the X position
        mX = -100;
 
        // Initializing the Y position
        mY = -100;
 
        // Initializing the paint object mPaint
        mPaint = new Paint();
 
        // Setting the color for the paint object
        mPaint.setColor(Color.BLUE);
 
    }
 
    public void resume(){
        // Instantiating the thread
        mThread = new Thread(this);
 
        // setting the mFlag to true for start repainting
        mFlag = true;
 
        // Start repaint the SurfaceView
        mThread.start();
    }
 
    public void pause(){
        mFlag = false;
    }
 
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        switch(event.getAction()){
        case MotionEvent.ACTION_DOWN:
            // Getting the X-Coordinate of the touched position
            mX = event.getX();
 
            // Getting the Y-Coordinate of the touched position
            mY = event.getY();
            break;
        }
        return true;
    }
 
    @Override
    public void run() {
        while(mFlag){
            // Check whether the object holds a valid surface
            if(!mHolder.getSurface().isValid())
                continue;
            // Start editing the surface
            Canvas canvas = mHolder.lockCanvas();
            // Draw a background color
            canvas.drawARGB(255, 255, 255, 255);
            // Draw a circle at (mX,mY) with radius 5
            canvas.drawCircle(mX, mY, 5, mPaint);
            // Finish editing the canvas and show to the user
            mHolder.unlockCanvasAndPost(canvas);
        }
    }
}
