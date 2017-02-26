
Stage s1(&pOPEN, 2);
Stage s2(&pH, 2);
Stage s3(&pE, 2);
Stage s4(&pL, 2);
Stage s5(&pOPEN, .2);
Stage s6(&pL, 2);
Stage s7(&pO, 2);

void setupStages(){
	int numStages = 7;
	Stage *stages[] = {&s1, &s2, &s3, &s4, &s5, &s6, &s7};

	for (int i = 0; i < numStages-1; ++i)
	{
		stages[i]->successor = stages[i+1];
	}
}