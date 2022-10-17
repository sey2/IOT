package org.techtown.myapplication;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button chosunBtn = findViewById(R.id.btn1);
        chosunBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Intent intent = new Intent(getApplicationContext(), ChosunActivity.class);
                Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://www3.chosun.ac.kr/chosun/index.do"));
                 startActivity(intent);
                startActivityForResult(intent, 101);
            }
        });

        Button naverBtn = findViewById(R.id.btn2);
        naverBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), NaverActivity.class);
                startActivity(intent);
            }
        });

        Button googleBtn = findViewById(R.id.btn3);
        googleBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), GoogleActivity.class);
                startActivity(intent);
            }
        });
    }

    /*
    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        
        if(requestCode == 101){
            Toast.makeText(getApplicationContext(), "OnActivityResult 호출" + requestCode + ", 결과 코드 : " + 
                    resultCode, Toast.LENGTH_LONG);
            
            if(resultCode == RESULT_OK){
                String name = data.getStringExtra("name");
                Toast.makeText(getApplicationContext(), "응답으로 전달된 name : " + name, Toast.LENGTH_LONG).show();
            }
                    
        }
    }
    
     */
}
