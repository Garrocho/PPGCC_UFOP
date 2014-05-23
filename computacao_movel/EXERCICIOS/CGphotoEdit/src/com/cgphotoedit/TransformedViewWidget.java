package com.cgphotoedit;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.view.View;

public class TransformedViewWidget extends View {
	
	public interface Transformation{
		void transform(Canvas canvas);
		String describe();
	}
	
	private final Transformation transformation;
	private final Drawable drawable;
	
	public TransformedViewWidget(Context ctx, Drawable draw, Transformation xform){
		super(ctx);
		
		drawable = draw;
		transformation = xform;
		
		setMinimumWidth(160);
		setMinimumHeight(135);
	}
	
	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec){
		setMeasuredDimension(getSuggestedMinimumWidth(), getSuggestedMinimumHeight());
	}
	
	@Override
	protected void onDraw(Canvas canvas){
		canvas.drawColor(Color.WHITE);
		canvas.save();
		transformation.transform(canvas);
		drawable.draw(canvas);
		canvas.restore();
		
		Paint paint = new Paint();
		paint.setColor(Color.BLACK);
		paint.setStyle(Paint.Style.STROKE);
		Rect r = canvas.getClipBounds();
		canvas.drawRect(r, paint);
		paint.setTextSize(10);
		paint.setColor(Color.BLUE);
		canvas.drawText(transformation.describe(), 5, getMeasuredHeight()-5, paint);
	}
}