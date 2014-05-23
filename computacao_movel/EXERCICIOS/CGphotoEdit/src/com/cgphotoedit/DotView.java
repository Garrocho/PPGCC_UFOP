package com.cgphotoedit;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.Point;
import android.view.Display;
import android.view.View;
import android.view.ViewGroup.LayoutParams;

public class DotView extends View {
	private final Dots dots;
	private Bitmap imagemSelecionada;
	private boolean drawDiameter = false;
	Paint paint = new Paint();
	public double distance(Dot d1, Dot d2) {
		return Math.sqrt( Math.pow( (d1.getX() - d2.getX()),2 ) + Math.pow( (d1.getY() - d2.getY()),2 ) );
	}

	@SuppressLint("NewApi")
	public DotView(Context context, Dots dots){
		super(context);
		this.dots = dots;
		Display display = ((Activity)context).getWindowManager().getDefaultDisplay();
		Point size = new Point();
		display.getSize(size);
		int width = size.x;
		int height = size.y;
		setMinimumWidth(width);
		setMinimumHeight(height / 2);
		this.setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
		setFocusable(true);
		this.setDrawingCacheEnabled(true);

		//setBackgroundResource(R.drawable.anagram_icon_256);
	}

	public void drawDiameter() {
		this.drawDiameter = true;
		this.invalidate();
	}

	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec){
		setMeasuredDimension(getSuggestedMinimumWidth(), getSuggestedMinimumHeight());		
	}

	public void clear(){
		dots.clearDots();
		imagemSelecionada = null;
		invalidate();
	}
	
	@Override
	protected void onDraw(Canvas canvas){
		canvas.drawColor(Color.WHITE);
		//canvas.drawBitmap(BitmapFactory.decodeResource(getResources(), R.drawable.anagram_icon_256), 0, 0, paint);
		if(imagemSelecionada != null)
			canvas.drawBitmap(imagemSelecionada, 0, 0, paint);
		paint.setStyle(Style.STROKE);
		paint.setColor(hasFocus() ? Color.BLUE : Color.GRAY);
		canvas.drawRect(0, 0, getWidth() - 1, getHeight() - 1, paint);
		paint.setStyle(Style.FILL);
		for (Dot dot : dots.getDots()) {
			paint.setColor(dot.getColor());
			canvas.drawCircle(dot.getX(), dot.getY(), dot.getDiameter(), paint);
		}

		if (this.drawDiameter) {
			double maxDistance = 0.0F;
			Dot ori = dots.getLastDot();
			Dot dst = ori;
			for (Dot d1 : dots.getDots()) {
				for (Dot d2 : dots.getDots()) {
					double currDistance = distance(d1, d2);
					if (currDistance > maxDistance) {
						ori = d1;
						dst = d2;
						maxDistance = currDistance;
					}
				}
			}
			canvas.drawLine(ori.getX(), ori.getY(), dst.getX(), dst.getY(), paint);
			this.drawDiameter = false;
		}
		
	}

	public Bitmap getImagem(){
		//return this.getDrawingCache();
		Bitmap image = Bitmap.createBitmap(this.getWidth(), this.getHeight(), Bitmap.Config.RGB_565);
		this.draw(new Canvas(image));
		return image;
	}

	public Bitmap getImagemSelecionada() {
		return imagemSelecionada;
	}

	public void setImagemSelecionada(Bitmap imagemSelecionada) {
		this.imagemSelecionada = imagemSelecionada;
	}


}
