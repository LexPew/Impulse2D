#pragma once	
#include <vector>


#include "ParticleForceGenerator.h"
#include "Particle.h"

namespace Impulse2D
{
	/**
	 * Stores all the particle force generators and their respective particles
	 */
	class ParticleForceRegistry
	{
	protected:

		/**
		 * Holds a pointer to the particle and the force generator associated with it
		 */
		struct RegistryEntry
		{
			Particle* Particle;
			ParticleForceGenerator* ForceGenerator;

			bool operator==(const RegistryEntry& p_entry) const
			{
				return Particle == p_entry.Particle && ForceGenerator == p_entry.ForceGenerator;
			}
		};

		/**
		 * Holds all the registry entries
		 */
		std::vector<RegistryEntry> Registry;

	public:
		/**
		 * Adds a new particle and its respective force generator to the registry
		 */
		void AddEntry(Particle* p_particle, ParticleForceGenerator* p_forceGenerator)
		{
			RegistryEntry nEntry = { p_particle, p_forceGenerator };
			Registry.push_back(nEntry);
		}

		/**
		 * Removes a give registered pair from the registry
		 */
		void RemoveEntry(Particle* p_particle, ParticleForceGenerator* p_forceGenerator)
		{
			RegistryEntry dEntry = { p_particle, p_forceGenerator };

			for(int i = 0; i < Registry.size(); i++)
			{
				if (Registry[i] == dEntry)
				{
					Registry.erase(Registry.begin() + i);
					break;
				}

			}

		}

		/**
		 * Clears the registry, does not delete any memory simply removes them from the registry vector
		 */
		void Clear()
		{
			Registry.clear();
		}

		/**
		 * Calls all the force generators to update the forces on their respective particles
		 */
		void UpdateForces(const float p_time) 
		{
			for (auto entry : Registry)
			{
				entry.ForceGenerator->UpdateForce(entry.Particle, p_time);
			}
		}

	};
}
