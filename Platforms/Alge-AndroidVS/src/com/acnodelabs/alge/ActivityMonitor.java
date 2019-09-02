package com.acnodelabs.alge;

import android.app.Activity;
import android.content.Context;

public class ActivityMonitor {

	Activity[] array;
	short index;
	
	ActivityMonitor() {
		array = new Activity[10];
		for (int i=0; i<10;i++) array[i]=null;
		index = 0;
	}
	
	public void Reg(Activity act) {
		array[index] = act;
		index++;
	}
	
	public void UnReg(Activity act) {
		for (int i=0; i<10;i++) { 
			if (array[i] == act) {
				array[i] = null;
			}	
		}
	}
	
}
