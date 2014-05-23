package com.cgphotoedit;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class Dots {
	public interface DotsChangeListener{
		void onDotsChange(Dots dots);
	}
	
	private final LinkedList<Dot> dots = new LinkedList<Dot>();
	private final List<Dot> safeDots = Collections.unmodifiableList(dots);
	
	private DotsChangeListener dotsChangeListener;
	
	public void setDotsChangeListener(DotsChangeListener l){
		this.dotsChangeListener = l;
	}
	
	public Dot getLastDot(){
		return (dots.size() <= 0) ? null : dots.getLast();
	}
	
	public List<Dot> getDots(){
		return safeDots;
	}
	
	public void addDot(float x, float y, int color, int diameter){
		dots.add(new Dot(x, y, color, diameter));
		this.notifyListener();		
	}
	
	public void clearDots(){
		dots.clear();
		this.notifyListener();
	}
	
	private void notifyListener(){
		if (this.dotsChangeListener != null){
			dotsChangeListener.onDotsChange(this);
		}
	}
}