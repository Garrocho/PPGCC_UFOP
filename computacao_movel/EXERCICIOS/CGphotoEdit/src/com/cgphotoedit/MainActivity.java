package com.cgphotoedit;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Random;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.provider.MediaStore.Images.Media;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Toast;

final class TrackingTouchListener implements View.OnTouchListener{
	private final Dots mDots;

	public TrackingTouchListener(Dots dots){
		mDots = dots;
	}

	private void addDot(Dots dots, float x, float y, float p, float s){
		dots.addDot(x, y, Color.BLUE,
				(int) ((p * s * MainActivity.DOT_DIAMETER) + 1));
	}

	@Override
	public boolean onTouch(View v, MotionEvent evt){
		switch (evt.getAction()){
		case MotionEvent.ACTION_DOWN:
			break;
		case MotionEvent.ACTION_MOVE:
			for (int i = 0, n = evt.getHistorySize(); i < n; i++){
				addDot(mDots, evt.getHistoricalX(i), evt.getHistoricalY(i),
						evt.getHistoricalPressure(i), evt.getHistoricalSize(i));
			}
			break;
		default:
			return false;
		}

		addDot(mDots, evt.getX(), evt.getY(), evt.getPressure(), evt.getSize());
		return true;
	}
}

public class MainActivity extends Activity {

	public static final int DOT_DIAMETER = 10;
	private EditText etX = null;
	private EditText etY = null;
	private Button btnRed = null;
	private Button btnGreen = null;
	final Dots dotModel = new Dots();
	DotView dotView;
	private  Button bt_draw_line;
	private  Button bt_limpar;

	private Random rand = new Random();

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		dotView = new DotView(this, dotModel);

		setContentView(R.layout.fragment_main);
		((LinearLayout)findViewById(R.id.root)).addView(dotView, 0);

		etX = (EditText)findViewById(R.id.et_x);
		etY = (EditText)findViewById(R.id.et_y);
		btnRed = (Button)findViewById(R.id.btn_red);
		btnGreen = (Button)findViewById(R.id.btn_green);
		bt_draw_line = (Button)findViewById(R.id.btn_draw_line);
		bt_draw_line.setVisibility(View.GONE);
		bt_limpar = (Button)findViewById(R.id.btn_limpar);
		bt_limpar.setVisibility(View.GONE);

		btnRed.setOnClickListener(new Button.OnClickListener(){
			@Override
			public void onClick(View v){
				makeDot(dotModel, dotView, Color.RED);
				bt_draw_line.setVisibility(View.VISIBLE);
				bt_limpar.setVisibility(View.VISIBLE);
			}
		});

		btnGreen.setOnClickListener(new Button.OnClickListener(){
			@Override
			public void onClick(View v){
				makeDot(dotModel, dotView, Color.GREEN);
				bt_draw_line.setVisibility(View.VISIBLE);
				bt_limpar.setVisibility(View.VISIBLE);
			}
		});

		dotModel.setDotsChangeListener(new Dots.DotsChangeListener() {

			@Override
			public void onDotsChange(Dots dots) {
				// TODO Auto-generated method stub
				Dot d = dots.getLastDot();
				etX.setText((null == d) ? "" : String.format("%.2f", d.getX()));
				etY.setText((null == d) ? "" : String.format("%.2f", d.getY()));
				dotView.invalidate();
			}
		});

		dotView.setOnTouchListener(new TrackingTouchListener(dotModel));
	}
	
	public void draw_line(View comp) {
		if (bt_draw_line.getVisibility() == View.VISIBLE)
			dotView.drawDiameter();
	}
	
	public void limpar(View comp) {
		if (bt_limpar.getVisibility() == View.VISIBLE) {
			etX.setText("");
			etY.setText("");
			dotView.clear();
			bt_limpar.setVisibility(View.GONE);
			bt_draw_line.setVisibility(View.GONE);
		}
	}
	
	public void abrir(View comp) {
		Intent photoPickerIntent = new Intent(Intent.ACTION_GET_CONTENT);
		photoPickerIntent.setType("image/*");
		startActivityForResult(photoPickerIntent, 1);
	}
	
	public void salvar(View comp) {
		Bitmap bitmap = dotView.getImagem();
		saveImage(this, bitmap, "imagem_galeria.jpg");
		bitmap.recycle();
	}
	
	void makeDot(Dots dots, DotView view, int color){
		int pad = (DOT_DIAMETER + 2) * 2;
		dots.addDot(DOT_DIAMETER + (rand.nextFloat() * (view.getWidth() - pad)), 
				DOT_DIAMETER + (rand.nextFloat() * (view.getHeight() - pad)), 
				color, DOT_DIAMETER);
	}

	public void saveImage(Context context, Bitmap bitmap, String name){

		MediaStore.Images.Media.insertImage(getContentResolver(), bitmap, name , "Criada com ExercicioGaleria");
		Toast.makeText(this, "A Imagem Foi Salva na Galeria!", Toast.LENGTH_SHORT).show();
	}

	private void setImagemFundo(Bitmap bitmap){
		etX.setText("");
		etY.setText("");
		dotView.clear();
		dotView.setImagemSelecionada(bitmap);
		dotModel.clearDots();
		dotView.invalidate();
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode == RESULT_OK)
		{
			Uri chosenImageUri = data.getData();

			Bitmap mBitmap = null;
			try {
				mBitmap = Media.getBitmap(this.getContentResolver(), chosenImageUri);
				setImagemFundo(mBitmap);
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}