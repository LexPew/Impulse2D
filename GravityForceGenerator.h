#pragma once
#include "ParticleForceGenerator.h"

namespace Impulse2D
{
	class GravityForceGenerator : public ParticleForceGenerator
	{
	protected:
		/**
		 * Holds the current gravity to be applied to particles
		 */
		Vector2 Gravity{ 0,9.81f };

	public:

		/**
		 * Creates a new Gravity force generator with the input gravity value
		 */
		GravityForceGenerator(const Vector2& p_gravity)
		{
			Gravity = p_gravity;
		}

		/**
		 * Updates the current gravity to the input value
		 */
		void SetGravity(const Vector2& p_gravity)
		{
			Gravity = p_gravity;
		}

		/**
		 * Returns the current gravity
		 */
		const Vector2& GetGravity() const
		{
			return Gravity;
		}

		/**
		 * Calculates a forces and applies it to the given particle
		 * @param p_particle Particle requesting the force
		* @param p_time Time-step
		*/
		void UpdateForce(Particle* p_particle, float p_time) override
		{
			if (!p_particle->HasFiniteMass()) { return; }
			p_particle->AddForce(Gravity * p_particle->GetMass());
		}
	};
}
