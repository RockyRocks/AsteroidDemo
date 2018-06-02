#include "..\..\game\objects\Enemy.h"
#include "..\..\common\utils\Utils.h"
#include "..\..\common\utils\MathLib.h"
#include "d3dx9math.h"
using namespace std;

class Boid:public Enemy
{
public:
	Boid(void);
   ~Boid(void);
void initialise();
void update();

D3DXVECTOR2 cohesion(vector<Boid> * neighbors,int noNeighbors);
/* Returns the recommended steering to keep seperation with nearby boids */
D3DXVECTOR2 seperation(vector<Boid> * neighbors,int noNeighbors);
/* Returns the recommended steering to keep alignment with nearby boids */
D3DXVECTOR2 alignment(vector<Boid> * neighbors,int noNeighbors);
/* Returns the recommended steering to keep within the screen space*/
D3DXVECTOR2 bounds();
/* Returns the recommended steering to avoid other flocks of boids*/
D3DXVECTOR2 Avoid(vector<Boid> * neighbors,int noNeighbors);
/* sets the velocity to the limit value if the current velocity is larger */
void limitVelocity(float limit);
/* Sets the correct orientation based on the velocity*/
float GetNewOrientaton(float curOri,D3DXVECTOR2 velocity);
/* Resets the boid with a random position and velocity */
void resetBoid();
/* Get and set methods for the maximum speed */
int MaxSpeed() const;
void MaxSpeed(int val);
/* Get and set methods for the Avoidance threshold value */
int AvoidThreshold() const;
void AvoidThreshold(int val);
/* Get and set methods for the Separation threshold value */
int SeperationThreshold() const;
void SeperationThreshold(int val);

D3DXVECTOR2 Velocity() const;
void Velocity(D3DXVECTOR2 val);
void controlforenemystates();

};