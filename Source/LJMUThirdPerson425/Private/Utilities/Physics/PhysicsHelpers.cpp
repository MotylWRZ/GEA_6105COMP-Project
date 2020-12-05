// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/Physics/PhysicsHelpers.h"

//--------Projectile Motion--------------------

// Get rotator required to hit specified coordinate
float UPhysicsHelpers::GetAngleRequiredToHitCoordinate(FVector SourceLocation, FVector TargetLocation, float Velocity, float GravityScale)
{
	float tGravity = 980.0f * GravityScale;
	float tVelocity = Velocity;

	// Pre-calculate the square roots for Velocity
	float tVelSqrt = FMath::Sqrt(tVelocity);
	float tVelSqrtSqrt = FMath::Sqrt(tVelSqrt);

	// Calculate 2D vector from the source and target locations
	FVector2D tXY = FVector2D(SourceLocation.X - TargetLocation.X,
							  SourceLocation.Y - TargetLocation.Y);

	// Calculate the Z coordinate separately
	float tZ = SourceLocation.Z - TargetLocation.Z;

	// Calculate the square root of tXY vector lenght
	// and multiply it by gravity value
	float tXYVecSqrt = tXY.SizeSquared() * tGravity;

	// tZ value multiplied by tVelSqrt
	float tZVelSqrt = tZ * tVelSqrt;

	float tEq = tVelSqrtSqrt - (tXYVecSqrt + tZVelSqrt * tGravity);

	// Calculate the square root of the equation result
	float tEqSqrt = FMath::Sqrt(tEq);

	float tDegreeA = tEqSqrt + tVelSqrt;
	float tDegreeB = tEqSqrt - tVelSqrt;

	float tFinalAngle = FMath::Min(tDegreeA, tDegreeB);

	return tFinalAngle;
}