class Pose
{
public:
  float positions[NUM_SERVOS];

  Pose(float pinky = 0.0, float ring = 0.0, float middle = 0.0, float pointer = 0.0, float thumb = 0.0, float spread = 0.0){
    positions[0]=pinky;
    positions[1]=ring;
    positions[2]=middle;
    positions[3]=pointer;
    positions[4]=thumb;
    positions[5]=spread;
  }
};

class Stage
{
public:
	Pose *pose;
	float holdDuration;
	Stage *successor;

	Stage(Pose *pos, float duration = 1.0, Stage *succ = 0){
		pose = pos;
		holdDuration = duration;
		successor = succ;
	}
};

Pose pOPEN(0,0,0,0);
Pose pCLOSED(1,1,1,1);
Pose pGUN(0,1,1,1);

void setupPoses(){

}
