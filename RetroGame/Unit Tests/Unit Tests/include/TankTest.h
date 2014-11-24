#ifndef _TANK_TEST_H_
#define _TANK_TEST_H_

const int iScreenWidth = 1280;
const int iScreenHeight = 780;

#pragma warning (disable : 4996)

void MoveTank();

Matrix4 StartMatrix;
float Speed;
float Rotation;
float delta;

void TankTest()
{
	Initialise(iScreenWidth, iScreenHeight);

	unsigned int Tank;
	Vec2 TankSize = Vec2( 64.f, 64.f );
	Vec2 TankOrigin = Vec2( 0.5f, 0.5f );
	Tank = CreateSprite( "./images/tank_topdown.png",  TankSize, TankOrigin );
	StartMatrix = Matrix4::IdentityMatrix;
	delta = GetDeltaTime();

	do 
	{
		Speed = 0;
		Rotation = 0.1f;
		ClearScreen();
		char Buff[50];
		DrawString( "Position:", 0, 0 );
		sprintf( Buff, "%f, %f, %f, %f", StartMatrix.m_11, StartMatrix.m_12, StartMatrix.m_13, StartMatrix.m_14 );
		DrawString( Buff, 0, 30 );
		sprintf( Buff, "%f, %f, %f, %f", StartMatrix.m_21, StartMatrix.m_22, StartMatrix.m_23, StartMatrix.m_24 );
		DrawString( Buff, 0, 60 );
		sprintf( Buff, "%f, %f, %f, %f", StartMatrix.m_31, StartMatrix.m_32, StartMatrix.m_33, StartMatrix.m_34 );
		DrawString( Buff, 0, 90 );
		sprintf( Buff, "%f, %f, %f, %f", StartMatrix.m_41, StartMatrix.m_42, StartMatrix.m_43, StartMatrix.m_44 );
		DrawString( Buff, 0, 120 );



		if ( IsKeyDown('W') )
		{
			Speed += 10.f * delta;

			float X = Speed  * sinf( (float)Maths::DegToRad(Rotation));
			float Y = Speed  * cosf( (float)Maths::DegToRad(Rotation));
	

			StartMatrix += Vec3( X, Y, 0.f );
		}

		if ( IsKeyDown('A') )
		{
			Rotation += 3.f;
				
			Matrix4 m4Rotate;
			m4Rotate.RotateMatrixZ( (float)Maths::DegToRad(Rotation * delta) );
			StartMatrix = m4Rotate * StartMatrix;
		}

		if ( IsKeyDown('S') )
		{
			
		}

		if ( IsKeyDown('D') )
		{
			Rotation -= 3.f;
				
			Matrix4 m4Rotate;
			m4Rotate.RotateMatrixZ( (float)Maths::DegToRad(Rotation * delta) );
			StartMatrix = m4Rotate * StartMatrix;
		}	
		
		SetSpriteMatrix( Tank, StartMatrix );
		DrawSprite( Tank );


	} while ( FrameworkUpdate() == false );
	
	Shutdown();
}



#endif // _TANK_TEST_H_