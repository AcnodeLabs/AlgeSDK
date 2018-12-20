package com.acnodelabs.alge;
 
import java.io.File;
import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;
import java.io.InputStream;
import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.*;


import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Looper;
import android.os.Message;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.Toast;
import java.util.HashMap;
import java.util.HashMap;
import java.util.List;

public class BaseActivity extends Activity implements ALlistener {
	private  Context mContext;
	private Timer milli100;
	
	private class TT extends TimerTask {
		private BaseActivity da;
		TT(BaseActivity a) { 
			super();
			this.da = a;
		}  
		  
		public void run() {
			((DemoGLSurfaceView) da.mGLView).onTimer();
		}
	}   
	 
	public void ReadAsset(Context mContext, String fname) {
		try {
			InputStream i = mContext.getAssets().open(fname);
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	//   
	
	//Transfer All Assets on Application Data Directory
	public void xfer() {
		String all = null;  
		// Open resource tagged as resid
	 	try {
			String ass[] = getAssets().list("");
			all = new String();
			byte[] b = new byte[5*1024*1024];
			for (int i=0; i<ass.length; i++) {
				if (ass[i].indexOf(".")==-1) continue;
				String f_out = mContext.getFilesDir().getAbsolutePath() + "/" + ass[i];
			
				FileOutputStream fo = mContext.openFileOutput(ass[i], MODE_PRIVATE);		
				
				InputStream fi = getAssets().open(ass[i]); 
				int count = fi.read(b, 0, 5*1024*1024);
				all = all.concat( "\n" + ass[i] + "::" + count);
				if (count>=5*1024*1023) {
					UserToast(mContext, ass[i]+" Resource Too Large > 4.9MB");
				} else {
					fo.write(b, 0, count);
				}
				fi.close();
				fo.close();			
			}
			//UserToast(mContext, all);	
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		//UserToast(mContext, all);
	}
	
	static boolean xferred = false;  
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mContext = getBaseContext();
        xfer();xferred = true;
        mGLView = new DemoGLSurfaceView(this,(ALlistener)this);
        setContentView(mGLView);
	     AccelerometerManager.sensorManager = (SensorManager) mContext.getSystemService(Context.SENSOR_SERVICE);
	     AccelerometerManager.startListening((AccelerometerListener)mGLView);
	     milli100 = new Timer("m100",true);
	     TT tt = new TT(this);
	     milli100.scheduleAtFixedRate(tt, 0, 2000); 
	     //UserToast(this.getBaseContext(), "TIMER@100ms");
	}   

	AlertDialog b = null;
	public void UserMsg(Context co, String messag) {
		// TODO Auto-generated method stub
			AlertDialog.Builder alt_bld = new AlertDialog.Builder(this);
			alt_bld.setMessage(messag); 
			alt_bld.setCancelable(false);
			alt_bld.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
			// Action for 'Yes' Button
				dialog.cancel();
			} 
			});
			AlertDialog alert = alt_bld.create();
			// Title for AlertDialog
			alert.setTitle("Message");
			alert.show(); 
	}
			
	public void UserToast(Context con, String chars) {
		Toast a = Toast.makeText(con, chars, Toast.LENGTH_LONG); 
		a.show();
	}
	
	public void SetTitle(String chars) {
        this.setTitleColor(Color.WHITE);
        this.setTitle(chars);
	} 
	  
	public boolean onKeyDown(int code, KeyEvent event) {
		mGLView.onKeyDown(code, event);
		return true;
	}
	  
    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }  
 
    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }
 
    private GLSurfaceView mGLView;

    static {
        System.loadLibrary("alge_app"); 
    }

	
}

class DemoGLSurfaceView extends GLSurfaceView implements AccelerometerListener { 
    
	int CMD_LOG =0x3001;
	int CMD_MSG =0x3002;
	int CMD_TITLE = 0x3013;
	int CMD_TEXID=0x3205;
	int CMD_BEGIN=0x1111;
	int CMD_END=0xffff;
	int CMD_SNDSET0= 0x3040; 
	int CMD_SNDSET1 =0x3041;
	int CMD_SNDSET2 =0x3042;
	int CMD_SNDSET3 =0x3043;
	int CMD_SNDPLAY0 =0x3050;
	int CMD_SNDPLAY1 =0x3051;
	int CMD_SNDPLAY2 =0x3052;
	int CMD_SNDPLAY3 =0x3053;
	int CMD_TEXSET0 =0x3230;
	int CMD_TEXSET1 =0x3231;
	int CMD_TEXSET2 =0x3232;
	int CMD_TEXSET3 =0x3233;
	int CMD_ALLSET =0x3993;
	int CMD_KEYDOWN =0x7998;
	int CMD_VIDSET =0x3007;
	int CMD_VIDPLAY =0x3008;
	int CMD_TOAST = 0x3022;    
	int CMD_TOUCH_START =0x3300;
	int CMD_TOUCH_END =0x3301;
	int CMD_TOUCHMOVE =0x3321;
	int CMD_SCREENSIZE = 0x3993;
	BaseActivity dem;
	ALlistener al;
 
	private float accelX;
	private float accelY;
	private float accelZ;
	
	
	public  SoundPool mSoundPool; 
	int[] soundid;

	Boolean supported = false;
		    /**
		     * Returns true if at least one Accelerometer sensor is available
		     */
	
	public void onTimer() {
		//while (pull()!=0) {
    		//FLUSHALL
    	//};
    	requestRender();
	}
	
	
	Puller puller;
	public class Puller implements Runnable {
		
		public DemoGLSurfaceView a;
		
		public void run() {
	  //      int doit =0;
	  //  while (doit!=CMD_END) {   
	   //      doit = a.pull();  
	    //    a.requestRender();
		//}
	    }
	}
	 //.
	public DemoGLSurfaceView(BaseActivity da, ALlistener al)  {
		super(da);
        dem = da;  
        //dem.UserToast(this.getContext(),"OpenGL Linked");
        this.al = al;
        mRenderer = new DemoRenderer(this.getContext(),dem, al);
        mRenderer.dgl = this;
        setRenderer(mRenderer);
        //this.getContext();
        //setRenderMode(RENDERMODE_WHEN_DIRTY);
        puller = new Puller();
        puller.a = this;
        //queueEvent(puller);
        soundid = new int[16];
	    mSoundPool = new SoundPool(16, AudioManager.STREAM_MUSIC, 0); 
	 	touchmoves = 0;
		 
		 android.util.DisplayMetrics display = this.getResources().getDisplayMetrics();

		 int width = display.widthPixels;
		 int height = display.heightPixels;
		nativePushI(CMD_SCREENSIZE, width, height);

		nativePushI(CMD_BEGIN,0,0);   
    }
   
	private synchronized void Play(int id) {
		AudioManager audioManager = (AudioManager) dem.getSystemService(Context.AUDIO_SERVICE);
		float actualVolume = (float) audioManager
		.getStreamVolume(AudioManager.STREAM_MUSIC);
		float maxVolume = (float) audioManager
		.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
		float volume = actualVolume / maxVolume;
		mSoundPool.play(id, volume, volume, 1, 0,  1.0f);
	}
	
	 public void onShake(float force) {
	     	//dem.UserMsg( "Phone shaked : " + force);
	    }
	      
	    /**    
	     * onAccelerationChanged callback   
	     */
	    public void onAccelerationChanged(float x, float y, float z) {
	    	mRenderer.SetAccel(x, y, z);
	    	pull();
	    }
			 
	int SoundID(int index) {
		int ID=index;
		
		//if (index==1) ID = R.raw.sound0;
		//if (index==2) ID = R.raw.sound1;
		
		return ID; 
	}     
	        
	int TexID(int index) {
		int ID=0; 		
	//	if (index==0) ID = R.raw.acnode;
		return ID;
	}      
	
	MediaPlayer[] mp = new MediaPlayer[16];
	MediaPlayer vmp = null;
	
	public int pull() {
	int cmd = nativePull();  
	
	if (cmd==CMD_ALLSET) {
	//	dem.UserMsg("AllSet");
		mRenderer.AllSet = true;
	} 
	
	if (cmd==CMD_TITLE || cmd==CMD_MSG || cmd==CMD_LOG || cmd==CMD_TOAST) {
		String title = nativeSzP1();
		try { 
			 
			if (cmd==CMD_TITLE) { 
				dem.SetTitle(title);
			};
			if (cmd==CMD_MSG) dem.UserMsg(this.getContext(),title);
			if (cmd==CMD_TOAST) dem.UserToast(this.getContext(),title);
			if (cmd==CMD_LOG) System.out.println("LOG:"+title);
		} catch (Exception e) {
			String a = e.getMessage();
		}
	}     

	
	
	if (cmd==CMD_VIDSET){
	    vmp = new MediaPlayer(); 
	    FileDescriptor fd;
		try { 
			String vfile = nativeSzP1();
			fd = dem.getAssets().openFd(vfile).getFileDescriptor();
			vmp.setDataSource(fd);
			//vmp.setDisplay(null);
			vmp.prepareAsync();
			//vmp.setDisplay();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	      
	}  
	    
	if (cmd==CMD_VIDPLAY){
	    try {
			
		    vmp.start(); 
		   // dem.UserMsg(this.getContext(),"Movie OK");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			dem.UserMsg(this.getContext(),e.getMessage());
		}
 
	}
	 
	if (cmd>=CMD_SNDSET0 && cmd<=CMD_SNDSET0+9) {
		int index =  (cmd - CMD_SNDSET0);
		boolean error = false;
		AssetFileDescriptor afd = null;
		String soundfile = nativeSzP1();
		try {	
			afd = dem.getAssets().openFd(soundfile);
			mp[index] = new MediaPlayer();
			mp[index].setDataSource(afd.getFileDescriptor(),afd.getStartOffset(), afd.getLength());
			mp[index].prepareAsync();
			
		} catch (IOException e) {   
			// TODO Auto-generated catch block
	 		e.printStackTrace();
			error = true;
		}
	}  
	 
	if (cmd>=CMD_SNDPLAY0 && cmd<=CMD_SNDPLAY0+9) {
		// Getting the user sound settings
		int index = cmd-CMD_SNDPLAY0;	
		if (mp[index]!=null) { 
			
			mp[index].setVolume(1,1);
			mp[index].start();
			
		} else dem.UserToast(getContext(), "Cannot SNDPLAY\nCheck Resource");
	}     
	 
	if (cmd>=CMD_TEXSET0 && cmd<=CMD_TEXSET3) { 
		//((DemoRenderer) mRenderer).texSet(cmd-CMD_TEXSET0, TexID(cmd - CMD_TEXSET0));		
		//nativePushI(CMD_TEXID, cmd-CMD_TEXSET0, (cmd-CMD_TEXSET0)+1);   		
	} 
	
	if (cmd==CMD_END) {		
		dem.finish();
	}
	
	  return cmd;
	 
	}//~
	
	private int Win32Key(int code) {
		int w =0;
		if (code>=8 && code<=16) w = code-8; //1-9
		if (code>=29 && code<=(29+26)) w = code - 13;//w = 27; //A-Z, e.g L on android=40 -> win32=27
		if (code==58) w=-10;//Rt Mapped on right Alt Key 
		if (code==57) w=-12;//Lt Mapped on left Alt Key 
		if (code==7) w=-1;//zero
		if (code==82) w=-11;//menu = test mode
		   
		return w;   
	}   
 
	public boolean onKeyDown(int code, KeyEvent event) {
	
    	pull();
		if (event.getAction() == KeyEvent.ACTION_DOWN) {
        	//int code = (int)event.getKeyCode();     
        	nativePushI(CMD_KEYDOWN, Win32Key(code),0); 
           // nativePause(); 
        }
		return true;    
	}
	
    public boolean onTouchEvent(final MotionEvent event) {
    	
    	pull();
    	int x = (int)event.getRawX();
    	int y = (int)event.getRawY();
    	
    
    	if (event.getAction() == MotionEvent.ACTION_MOVE) {
        	touchmoves++;
        	//Only send fifth move point as every call is expensive
        	//if (touchmoves>=5) {
				nativePushI(CMD_TOUCHMOVE, x,y);
        		touchmoves=0;
        	//}
        }  
    	
    	if (event.getAction() == MotionEvent.ACTION_DOWN) nativePushI(CMD_TOUCH_START, x,y);
    	if (event.getAction() == MotionEvent.ACTION_UP) nativePushI(CMD_TOUCH_END, x,y);
                	
        return true; 
    }
    int touchmoves;
    DemoRenderer mRenderer;

    private static native void nativePause();
    private static native void nativePushI(int cmd, int x, int y);
    private static native int nativePull();
    private static native String nativeSzP1();
    private static native int nativeIntP1();
    private static native int nativeIntP2();
    
} 

class DemoRenderer implements GLSurfaceView.Renderer  {
	 
	private Context con;
	
	public static boolean AllSet;
	 
    private BaseActivity acti;
	private ALlistener al;
    public DemoGLSurfaceView dgl;
    public ShortBuffer textureBuffer;
	public float accelX;
	public float accelY;
	public float accelZ;
	public String szAccel;
	public int texID0;
	public int texID1; 
	public int texID2;
	public int texID3;
	private GL10 gl;
	IntBuffer textures = IntBuffer.allocate(4);

   
	public void onTimer() {
		acti.UserToast(con, "Rendrer linked"); 
	}
	
	DemoRenderer(Context context, BaseActivity acti, ALlistener al) {
		super();
		this.al = al;
		this.con = context;
		this.acti = acti;
		accelX = 0;
		accelY = 0;
		accelZ = 0;
		  
		texID0 = 0;  
		texID1 = 0;
		texID2 = 0;
		texID3 = 0;
	    gl = null;
	    AllSet = false;
	    
	    
	  //  acti.UserMsg(con, "Rendrer linked"); 
	}
	
	// Scale accel values to Angle
	// x10 to give resolution of 0.1 Degree
	// accelX = 123 means angle of 12.3
	public void SetAccel(float x, float y, float z) {
		
		//GOOD FOR ZTILT ONLY
		int decimalplaces = 1;
		accelX = (accelX+(int)(10* decimalplaces * 10 * x))/2;
		accelY = (accelY+(int)(10* decimalplaces * 10 * y))/2;
		accelZ = (accelZ+(int)(10* decimalplaces * 10 * z))/2;
		 
		//FOR NOW PASS ACTUALVALUES x 100 as integer
		//
		accelX = x * 100; 
		accelY = y * 100;
		accelZ = z * 100;    
	}
		
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    		 this.gl = gl;    			 
       	     nativeInit(con.getFilesDir().getAbsolutePath()); 
    }
 
    public void onSurfaceChanged(GL10 gl, int w, int h) {
        nativeResize(w, h);      
    }    
 
    public void onDrawFrame(GL10 gl) {
        nativeRender((int)accelX,(int)accelY, (int)accelZ);   
     } 
   
    private static native void nativeInit(String respath); 
    private static native void nativeResize(int w, int h);          
    private static native void nativeRender(int ax100, int ay100, int az100);
    private static native void nativeDone();
   
} 
//.. 

