#include "Boid.h"

Boid::Boid( void )
{
	int maxSpeed = 10;
	int avoidThreshold = 200;
	int seperationThreshold = 100;
}

Boid::~Boid( void )
{

}

void Boid::initialise()
{
	Sprite.SetPosition(Util::RandomInt(0,1024),Util::RandomInt(0,768)); 
	Velocity(D3DXVECTOR2(Util::randFloat(-5,5),Util::randFloat(-5,5)));
	//maxSpeed = 10;
	//avoidThreshold = 200;
	//seperationThreshold = 100;
}

void Boid::update(vector<Boid> * red,int noRedBoids,vector<Boid> * green,int noGreenBoids,vector<Boid> * blue,int noBlueBoids)
{

	theNoRedBoids = noRedBoids;
	theNoGreenBoids = noGreenBoids;
	theNoBlueBoids = noBlueBoids;
	D3DXVECTOR2 theCohesion,theSeperation,theAlignment,theBounds,avoidCol1,avoidCol2;

	// If the Boid is red then get the steering recommendations.
	if (getType()==Red)
	{
		theCohesion = cohesion(red,noRedBoids);
		theSeperation = seperation(red,noRedBoids);
		theAlignment = alignment(red,noRedBoids);
		theBounds = bounds();
		avoidCol1  = Avoid(green,noGreenBoids);
		avoidCol2  = Avoid(blue,noBlueBoids);
	}
	// If the Boid is Blue then get the steering recommendations.
	if (getType()==Blue)
	{
		theCohesion = cohesion(blue,noBlueBoids);
		theSeperation = seperation(blue,noBlueBoids);
		theAlignment = alignment(blue,noBlueBoids);
		theBounds = bounds();
		avoidCol1  = Avoid(green,noGreenBoids);
		avoidCol2  = Avoid(red,noRedBoids);
	}
	// If the Boid is Green then get the steering recommendations.
	if (getType()==Green)
	{
		theCohesion = cohesion(green,noGreenBoids);
		theSeperation = seperation(green,noGreenBoids);
		theAlignment = alignment(green,noGreenBoids);
		theBounds = bounds();
		avoidCol1  = Avoid(red,noRedBoids);
		avoidCol2  = Avoid(blue,noBlueBoids);
	}

	/*Add the Steering recommendations together with the current velocity without weighting
	to get the final velocity. */
	Velocity(Velocity()+theCohesion+theAlignment+theSeperation+theBounds+avoidCol1+avoidCol2);

	//Limit the velocity to the maximum speed
	limitVelocity(maxSpeed);

	//Set the position and Orientation based on the velocity
	setPosition(getPos()+ Velocity());
	Sprite.SetRotation(-D3DXToDegree(GetNewOrientaton(0,Velocity())));

}

void Boid::SetType(BoidType theType)
{
	type = theType;
}

BoidType Boid::getType()
{
	return type;
}

D3DXVECTOR2 Boid::Velocity() const
{
	return velocity;
}

void Boid::Velocity( D3DXVECTOR2 val )
{
	velocity = val;
}

/*The Cohesion function  attepmts to steer towards the average postion of the flock. */
D3DXVECTOR2 Boid::cohesion(vector<Boid> * neighbors,int noNeighbors)
{
	//Create storage for the eventual output
	D3DXVECTOR2 output;
	output.x=0;
	output.y=0;

	//if their are no neighbors then return no steering.
	if (noNeighbors <=1)
	{
		return output;
	}

	//For each Neighbor
	for (int i=0; i< noNeighbors; i++)
	{
		//an if check to make sure it ignores itself
		if (neighbors->at(i).getPos() != getPos())
		{
			//add the neighbors position to the output.
			output += neighbors->at(i).getPos();
		}	
	}

	//Find the average position and then scale the result by 100
	output = Util::VectorDivide(output,noNeighbors-1);
	output = Util::VectorDivide(output - getPos(),100); 

	//return the resulting steering
	return output;
}

/*The Separation function attempts to steer away from nearby boids. */
D3DXVECTOR2 Boid::seperation(vector<Boid> * neighbors,int noNeighbors)
{
	//Create storage for the eventual output
	D3DXVECTOR2 output;
	output.x=0;
	output.y=0;

	//For each Neighbor
	for (int i=0; i< noNeighbors; i++)
	{
		//an if check to make sure it ignores itself
		if (neighbors->at(i).getPos() != getPos())
		{
			//Calculate the distance between the positions
			D3DXVECTOR2 distance = neighbors->at(i).getPos() - getPos();

			// If the distance is less then the threshold
			if (D3DXVec2Length(&distance) < seperationThreshold)
			{
				//calculate the strength and direction of the repulsion
				float strength = -0.5 * (seperationThreshold - D3DXVec2Length(&distance))/seperationThreshold;		 
				D3DXVECTOR2 thisOutput = strength * Util::vector2Normalise(distance);

				//add the result to the output
				output += thisOutput;

			}
		}
	}
	// return the final steering recommendation
	return output;
}

/*The Avoid function attempts to steer away from other flocks. */
D3DXVECTOR2 Boid::Avoid(vector<Boid> * neighbors,int noNeighbors)
{
	//Create storage for the eventual output
	D3DXVECTOR2 output;
	output.x=0;
	output.y=0;

	//for each neighbor
	for (int i=0; i< noNeighbors; i++)
	{
		//an if check to make sure it ignores itself
		if (neighbors->at(i).getPos() != getPos())
		{
			//Calculate the distance between the positions
			D3DXVECTOR2 distance = neighbors->at(i).getPos() - getPos();

			// If the distance is less then the threshold
			if (D3DXVec2Length(&distance) < avoidThreshold)
			{
				//calculate the strength and direction of the repulsion
				float strength = -0.5 * (avoidThreshold - D3DXVec2Length(&distance))/avoidThreshold;		
				D3DXVECTOR2 thisOutput = strength * Util::vector2Normalise(distance);
				//Add the result to the current output value
				output += thisOutput;
			}
		}
	}

	//return the final Output
	return output;
}

/*The alignment function attempts to steer towards the average velocity of other boids */
D3DXVECTOR2 Boid::alignment(vector<Boid> * neighbors,int noNeighbors)
{
	//Create storage for the eventual output
	D3DXVECTOR2 output;
	output.x=0;
	output.y=0;

	//If there are no neighbors return no steering
	if (noNeighbors <=1)
	{
		return output;
	}

	//For each neighbor
	for (int i=0; i< noNeighbors; i++)
	{
		//an if check to make sure it ignores itself
		if (neighbors->at(i).getPos() != getPos())
		{
			//Add the velocity to the output.
			output = output + neighbors->at(i).Velocity();
		}	
	}

	//find and return the average velocity scaled by 8
	output = Util::VectorDivide(output,noNeighbors-1);
	return Util::VectorDivide(output - Velocity(),8);
}

void Boid::limitVelocity( float limit )
{
	D3DXVECTOR2 theCurrentVelocity = Velocity();
	if (D3DXVec2Length(&theCurrentVelocity) > limit)
	{  
		theCurrentVelocity =  Util::vector2Normalise(theCurrentVelocity) * limit;
		Velocity(theCurrentVelocity);
	}
}

float Boid::GetNewOrientaton(float curOri,D3DXVECTOR2 velocity)
{
	return atan2(velocity.x,-velocity.y);
}

/*The Bounds function attempts to steer towards the screen if the boids leave */
D3DXVECTOR2 Boid::bounds()
{
	D3DXVECTOR2 output;
	output.x=0;
	output.y=0;

	int minX=-40,maxX=1064,minY=-40,MaxY=798;

	if (getPos().x > maxX)
	{
		output.x = -1;
	}
	if (getPos().x < minX)
	{
		output.x = 1;
	}

	if (getPos().y > MaxY)
	{
		output.y = -1;
	}
	if (getPos().y < minY)
	{
		output.y = 1;
	}

	return output;
}

void Boid::resetBoid()
{
	Sprite.SetPosition(Util::RandomInt(0,1024),Util::RandomInt(0,768)); 
	Velocity(D3DXVECTOR2(Util::randFloat(-5,5),Util::randFloat(-5,5)));
}

int Boid::MaxSpeed() const
{
	return maxSpeed;
}

void Boid::MaxSpeed( int val )
{
	maxSpeed = val;
}

int Boid::AvoidThreshold() const
{
	return avoidThreshold;
}

void Boid::AvoidThreshold( int val )
{
	avoidThreshold = val;
}

int Boid::SeperationThreshold() const
{
	return seperationThreshold;
}

void Boid::SeperationThreshold( int val )
{
	seperationThreshold = val;
}

