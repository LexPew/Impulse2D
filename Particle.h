#pragma once
#include "Vector2.h"

namespace Impulse2D
{
	/**
	 * A particle is the simplest object possible to simulate as it only has a position, velocity and mass.
	*/
	class Particle
	{
	protected:
		/**
		 * Holds the linear position of the particle in world space
		 */
		Vector2 Position;

		/**
		 * Holds the linear velocity of the particle in world space
		 */
		Vector2 Velocity;

		/**
		 * Holds the linear acceleration of the particle.
		 */
		Vector2 Acceleration;

		/**
		 * Holds the accumulated forces to be applied at the next simulation step, this is rest to zero at the end of each step. 
		 */
		Vector2 ForceAccumulation{0,0};


		/**
		 * Holds the drag force that will act upon the particle slowing its velocity over time
		 */
		float Drag{ 0.9995f };


		/**
		 * Holds the inverse of the mass of the particle. More useful to hold as you can do a = F*1/m which is cheaper than dividing, aka a = f/m
		 * Set to 0.1f by default to simulate mass of 10kg
		 */
		float InverseMass{ 0.1f };

	public:
		/**
		 * Creates a new particle with a default position of 0,0 and no initial velocity, and a mass of 10kg
		 */
		Particle() = default;

		/**
		 * Creates a new particle with an input position, velocity and mass
		 */
		Particle(const Vector2& p_position, const Vector2& p_velocity, const Vector2& p_acceleration, const float p_mass)
		{
			Position = p_position;
			Velocity = p_velocity;
			Acceleration = p_acceleration;

			SetMass(p_mass);
		}

		/**
		 *	GETTERS AND SETTERS
		 */



		/**
		 * Returns the position of the particle
		 */
		const Vector2& GetPosition() const
		{
			return Position;
		}


		/**
		 * Sets the mass of the object
		 */
		void SetMass(const float p_newMass)
		{
			if (p_newMass > 0)
			{
				InverseMass = 1 / p_newMass;
			}

		}


		/**
		 * Returns the mass of the object
		 */
		float GetMass() const
		{
			return 1.0f / InverseMass;
		}

		/**
		 * Returns a bool based on whether the mass is finite aka non-infinite 
		 */
		bool HasFiniteMass() const
		{
			return InverseMass > 0;
		}
		/**
		 * Directly sets the inverse mass of the object, use with caution
		 */
		void SetInverseMass(const float p_newInverseMass)
		{
			InverseMass = p_newInverseMass;
		}


		/**
		 * Returns the kinetic energy store by the object
		 */
		float GetKineticEnergy() const
		{
			return 0.5f * GetMass() * Velocity.Magnitude() * Velocity.Magnitude();
		}

		void AddForce(const Vector2& p_force)
		{
			ForceAccumulation += p_force;
		}
		/**
		 * Clears any accumulated forces 
		 */
		void ClearForces()
		{
			ForceAccumulation.Clear();
		}
		/**
		 * Integrates a particle over time.
		 */
		void Integrate(const float p_time)
		{
			//Integration is used to find the position and velocity of an object over time,
			//based on its current velocity, acceleration, and initial conditions.

			//Don't integrate things with infinite mass
			if (InverseMass <= 0) { return; }

			//Update position (position = velocity *time)
			Position.AddScaledVector(Velocity, p_time);


			/*
			*This section calculates acceleration which is following the formula A = F/M though since we are using inverse mass for optimization as division is more
			*resource heavy than multiplication it is A = Fx1/M to A = F*InverseMass, then we add to the velocity using final velocity formula v = u + at
			*where v is our final velocity(what we want to calculate), u is the initial velocity(the velocity current to this frame), a is acceleration *  time.
			*/

			Vector2 resultingAcceleration = Acceleration;
			resultingAcceleration.AddScaledVector(ForceAccumulation, InverseMass);
			Velocity.AddScaledVector(resultingAcceleration, p_time);


			//Impose drag, velocity *= drag(number between 0 & .99) to the power of time as with more time elapse the smaller drag becomes increasing drag due to multiplication
			Velocity *= pow(Drag, p_time);

			//Clear the accumulated forces from this time step
			ClearForces();
		}
	};
}

