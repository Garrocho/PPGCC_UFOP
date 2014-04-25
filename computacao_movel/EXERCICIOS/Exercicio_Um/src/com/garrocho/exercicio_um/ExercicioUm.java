package com.garrocho.exercicio_um;

import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;
import android.os.Bundle;

public class ExercicioUm extends ActionBarActivity {
	
	private TextView campoTextoUm, campoTextoDois;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_exercicio_um);
        
        campoTextoUm = (TextView)findViewById(R.id.exercicio_um_campo_texto_um);
        campoTextoDois = (TextView)findViewById(R.id.exercicio_um_campo_texto_dois);
    }
    
    public void validar(View componente) {
    	if (isAnagrama(campoTextoUm.getText().toString(), campoTextoDois.getText().toString()))
    		Toast.makeText(this, "E um Anagrama", Toast.LENGTH_SHORT).show();
    	else
    		Toast.makeText(this, "Nao e um Anagrama", Toast.LENGTH_SHORT).show();
    }
    
    public boolean isAnagrama(String texto1, String texto2) {
    	if (texto1.length() != texto2.length())
    		return false;
    	for (int i=0; i < texto1.length(); i++)
    		if (!texto2.contains(texto1.substring(i, i+1)))
    			return false;
    	return true;
    }
}
