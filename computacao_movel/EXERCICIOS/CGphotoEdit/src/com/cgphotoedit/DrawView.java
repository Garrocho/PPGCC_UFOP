package com.cgphotoedit;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.View;

public class DrawView extends View {
	
	private String text = "";
	
	public DrawView(Context ctx, String txt, int w, int h){
		super(ctx);
		text = txt;
		
		this.setMinimumWidth(w);
		this.setMinimumHeight(h);
	}
	
	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec){
		setMeasuredDimension(this.getSuggestedMinimumWidth(),
				this.getSuggestedMinimumHeight());
	}
	
	@Override
	protected void onDraw(Canvas canvas){
		canvas.drawColor(Color.WHITE);
		
		Paint paint = new Paint();
		paint.setColor(Color.MAGENTA);
		canvas.drawText(text, 25, 30, paint);
	}
}