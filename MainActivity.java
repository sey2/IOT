package org.techtown.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button chosunBtn = findViewById(R.id.btn1);
        chosunBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(), ChosunActivity.class);
                //Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://www3.chosun.ac.kr/chosun/index.do"));
                startActivity(intent);
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
}
