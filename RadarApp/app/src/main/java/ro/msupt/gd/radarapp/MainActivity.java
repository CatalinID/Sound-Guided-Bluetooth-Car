package ro.msupt.gd.radarapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    ImageView soundUp, soundDown, soundLeftUp, soundLeftDown, soundRightUp, soundRightDown, soundLeft, soundRight;

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef = database.getReference();
    DatabaseReference conditionRef = myRef.child("location/position");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Get UI
        soundUp = (ImageView) findViewById(R.id.soundUp);
        soundDown = (ImageView) findViewById(R.id.soundDown);
        soundLeftUp = (ImageView) findViewById(R.id.soundLeftUp);
        soundRightUp = (ImageView) findViewById(R.id.soundRightUp);
        soundLeftDown = (ImageView) findViewById(R.id.soundLeftDown);
        soundRightDown = (ImageView) findViewById(R.id.soundRightDown);
        soundRight = (ImageView) findViewById(R.id.soundRight);
        soundLeft = (ImageView) findViewById(R.id.soundLeft);


    }

    @Override
    protected void onStart() {
        super.onStart();

        conditionRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String text = dataSnapshot.getValue(String.class);
                displayLocation(text);
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }

    private void displayLocation(String text) {
        switch (text) {
            case "Up":
                displayLocation("default");
                soundUp.setVisibility(View.VISIBLE);
                break;
            case "Down":
                displayLocation("default");
                soundDown.setVisibility(View.VISIBLE);
                break;
            case "Left":
                displayLocation("default");
                soundLeft.setVisibility(View.VISIBLE);
                break;
            case "LeftUp":
                displayLocation("default");
                soundLeftUp.setVisibility(View.VISIBLE);
                break;
            case "LeftDown":
                displayLocation("default");
                soundLeftDown.setVisibility(View.VISIBLE);
                break;
            case "Right":
                displayLocation("default");
                soundRight.setVisibility(View.VISIBLE);
                break;
            case "RightUp":
                displayLocation("default");
                soundRightUp.setVisibility(View.VISIBLE);
                break;
            case "RightDown":
                displayLocation("default");
                soundRightDown.setVisibility((View.VISIBLE));
                break;
            default:
                soundLeft.setVisibility(ImageView.INVISIBLE);
                soundUp.setVisibility(View.INVISIBLE);
                soundDown.setVisibility(View.INVISIBLE);
                soundRight.setVisibility(View.INVISIBLE);
                soundRightUp.setVisibility(View.INVISIBLE);
                soundRightDown.setVisibility(View.INVISIBLE);
                soundLeftUp.setVisibility(View.INVISIBLE);
                soundLeftDown.setVisibility(View.INVISIBLE);
        }
    }
}
