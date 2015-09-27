package com.superpowered.crossexample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.media.AudioManager;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import java.io.IOException;
import android.os.Build;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.Button;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    boolean playing = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Get the device's sample rate and buffer size to enable low-latency Android audio output, if available.
        String samplerateString = null, buffersizeString = null;
        if (Build.VERSION.SDK_INT >= 17) {
            AudioManager audioManager = (AudioManager) this.getSystemService(Context.AUDIO_SERVICE);
            samplerateString = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
            buffersizeString = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
        }
        if (samplerateString == null) samplerateString = "44100";
        if (buffersizeString == null) buffersizeString = "512";

        // Files under res/raw are not compressed, just copied into the APK. Get the offset and length to know where our files are located.
        AssetFileDescriptor fd0 = getResources().openRawResourceFd(R.raw.master),
                fd1 = getResources().openRawResourceFd(R.raw.voxmainq),
                fd2 = getResources().openRawResourceFd(R.raw.voxharmonyq),
                fd3 = getResources().openRawResourceFd(R.raw.padsguitarq),
                fd4 = getResources().openRawResourceFd(R.raw.pluckq),
                fd5 = getResources().openRawResourceFd(R.raw.commentary),
                fd6 = getResources().openRawResourceFd(R.raw.ashley);
        long[] params = {
                fd0.getStartOffset(),
                fd0.getLength(),
                fd1.getStartOffset(),
                fd1.getLength(),
                Integer.parseInt(samplerateString),
                Integer.parseInt(buffersizeString),
                fd2.getStartOffset(),
                fd2.getLength(),
                fd3.getStartOffset(),
                fd3.getLength(),
                fd4.getStartOffset(),
                fd4.getLength(),
                fd5.getStartOffset(),
                fd5.getLength(),
                fd6.getStartOffset(),
                fd6.getLength(),
        };
        try {
            fd0.getParcelFileDescriptor().close();
            fd1.getParcelFileDescriptor().close();
            fd2.getParcelFileDescriptor().close();
            fd3.getParcelFileDescriptor().close();
            fd4.getParcelFileDescriptor().close();
            fd5.getParcelFileDescriptor().close();
            fd6.getParcelFileDescriptor().close();
        } catch (IOException e) {
            android.util.Log.d("", "Close error.");
        }

        // Arguments: path to the APK file, offset and length of the two resource files, sample rate, audio buffer size.
        SuperpoweredExample(getPackageResourcePath(), params);

        // crossfader events
        final SeekBar fader = (SeekBar)findViewById(R.id.firstStemSeekBar);
        fader.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                onCrossfader(progress, 1);
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        final SeekBar fader2 = (SeekBar)findViewById(R.id.secondStemSeekBar);
        fader2.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                onCrossfader(progress, 2);
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        final SeekBar fader3 = (SeekBar)findViewById(R.id.thirdStemSeekBar);
        fader3.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                onCrossfader(progress, 3);
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        final SeekBar fader4 = (SeekBar)findViewById(R.id.fourthStemSeekBar);
        fader4.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                onCrossfader(progress, 4);
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        final SeekBar fader5 = (SeekBar)findViewById(R.id.fifthStemSeekBar);
        fader5.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                onCrossfader(progress, 5);
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        final SeekBar fader6 = (SeekBar)findViewById(R.id.sixthStemSeekBar);
        fader6.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                onCrossfader(progress, 6);
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        final SeekBar fader7 = (SeekBar)findViewById(R.id.seventhStemSeekBar);
        fader7.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                onCrossfader(progress, 7);
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });
    }


    public void SuperpoweredExample_PlayPause(View button) {  // Play/pause.
        playing = !playing;
        onPlayPause(playing);
        Button b = (Button) findViewById(R.id.playPause);
        b.setText(playing ? "Pause" : "Play");
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private native void SuperpoweredExample(String apkPath, long[] offsetAndLength);
    private native void onPlayPause(boolean play);
    private native void onCrossfader(int value, int stem);

    static {
        System.loadLibrary("SuperpoweredExample");
    }
}
