#pragma once
#include "Particle.h"


namespace Impulse2D
{
	/**
	 * A force generator can be asked to add a force to one or more particles
	 */
	class ParticleForceGenerator
	{
	public:

		/**
		 * Calculates a forces and applies it to the given particle
		 * @param p_particle Particle requesting the force
		 * @param p_time Time-step
		 */
		virtual void UpdateForce(Particle* p_particle, float p_time) = 0;
	};
}
