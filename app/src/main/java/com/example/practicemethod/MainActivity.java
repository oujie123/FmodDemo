package com.example.practicemethod;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.fmod.FMOD;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static final int MODE_NORMAL = 0;    // 正常
    private static final int MODE_GIRL = 1;      // 女孩
    private static final int MODE_UNCLE = 2;     // 大叔
    private static final int MODE_HORROR = 3;    // 恐怖
    private static final int MODE_FUN = 4;       // 搞怪
    private static final int MODE_ETHEREAL = 5;  // 空灵

    private Button btn_normal;
    private Button btn_girl;
    private Button btn_uncle;
    private Button btn_horror;
    private Button btn_fun;
    private Button btn_ethereal;
    private TextView tv;

    // Used to load the 'native-lib' library on application startup.
    static {
        // System.load("D://native.lib"); // 加载绝对路径的so库
        System.loadLibrary("native-lib");
    }

    private String path;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        path = "file:///android_asset/audio.m4a";

        initView();
        FMOD.init(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    private void initView() {
        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        btn_normal = findViewById(R.id.normal);
        btn_normal.setOnClickListener(this);

        btn_girl = findViewById(R.id.girl);
        btn_girl.setOnClickListener(this);

        btn_uncle = findViewById(R.id.uncle);
        btn_uncle.setOnClickListener(this);

        btn_horror = findViewById(R.id.horror);
        btn_horror.setOnClickListener(this);

        btn_fun = findViewById(R.id.fun);
        btn_fun.setOnClickListener(this);

        btn_ethereal = findViewById(R.id.ethereal);
        btn_ethereal.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.normal:
                tv.setText("Normal Mode");
                changeVoiceNative(MODE_NORMAL, path);
                break;
            case R.id.girl:
                tv.setText("Girl Mode");
                changeVoiceNative(MODE_GIRL, path);
                break;
            case R.id.uncle:
                tv.setText("Uncle Mode");
                changeVoiceNative(MODE_UNCLE, path);
                break;
            case R.id.horror:
                tv.setText("Horror Mode");
                changeVoiceNative(MODE_HORROR, path);
                break;
            case R.id.fun:
                tv.setText("Fun Mode");
                changeVoiceNative(MODE_FUN, path);
                break;
            case R.id.ethereal:
                tv.setText("Ethereal Mode");
                changeVoiceNative(MODE_ETHEREAL, path);
                break;
            default:
        }
    }

    public void playEnd(String str) {
        Toast.makeText(this, str, Toast.LENGTH_LONG).show();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void changeVoiceNative(int mode, String path);
}
