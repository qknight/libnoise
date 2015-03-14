// texturesky.cpp
//
// This program uses the libnoise library to generate texture maps consisting
// of water overlayed with clouds of varying density.
//
// Copyright (C) 2004 Jason Bevins
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// (COPYING.txt) for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc., 59
// Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The developer's email is jlbezigvins@gmzigail.com (for great email, take
// off every 'zig'.)
//

#include <noise/noise.h>

#include "noiseutils.h"

using namespace noise;

// Height of the texture.
const int TEXTURE_HEIGHT = 256;

// Creates the color gradients for the texture.
void CreateTextureColor (utils::RendererImage& renderer);

// Given two noise modules, this function renders two flat square texture maps
// and combines them to form a Windows bitmap (*.bmp) file.  Because the
// texture map is square, its width is equal to its height.  The final texture
// map can be seamless (tileable) or non-seamless.
void CreatePlanarTexture (const module::Module& lowerNoiseModule,
  const module::Module& upperNoiseModule, bool seamless, int height,
  const char* filename);

// Given two noise modules, this function renders two spherical texture maps
// and combines them to form a Windows bitmap (*.bmp) file.  The texture map's
// width is double its height.
void CreateSphericalTexture (const module::Module& lowerNoiseModule,
  const module::Module& upperNoiseModule, int height, const char* filename);

// Given two noise maps, this function renders two texture maps and combines
// them to form a Windows bitmap (*.bmp) file.
void RenderTexture (const utils::NoiseMap& lowerNoiseMap,
  const utils::NoiseMap& upperNoiseMap, const char* filename);

#include <iostream>

int main ()
{
  // This texture map is made up two layers.  The bottom layer is a wavy water
  // texture.  The top layer is a cloud texture.  These two layers are
  // combined together to create the final texture map.

  // Lower layer: water texture
  // --------------------------

  // Base of the water texture.  The Voronoi polygons generate the waves.  At
  // the center of the polygons, the values are at their lowest.  At the edges
  // of the polygons, the values are at their highest.  The values smoothly
  // change between the center and the edges of the polygons, producing a
  // wave-like effect.
  module::Voronoi baseWater;
  baseWater.SetSeed (0);
  baseWater.SetFrequency (8.0);
  baseWater.EnableDistance (true);
  baseWater.SetDisplacement (0.0);

  // Stretch the waves along the z axis.
  module::ScalePoint baseStretchedWater;
  baseStretchedWater.SetSourceModule (0, baseWater);
  baseStretchedWater.SetScale (1.0, 1.0, 3.0);

  // Smoothly perturb the water texture for more realism.
  module::Turbulence finalWater;
  finalWater.SetSourceModule (0, baseStretchedWater);
  finalWater.SetSeed (1);
  finalWater.SetFrequency (8.0);
  finalWater.SetPower (1.0 / 32.0);
  finalWater.SetRoughness (1);

  // Upper layer: cloud texture
  // --------------------------

  // Base of the cloud texture.  The billowy noise produces the basic shape
  // of soft, fluffy clouds.
  module::Billow cloudBase;
  cloudBase.SetSeed (2);
  cloudBase.SetFrequency (2.0);
  cloudBase.SetPersistence (0.375);
  cloudBase.SetLacunarity (2.12109375);
  cloudBase.SetOctaveCount (4);
  cloudBase.SetNoiseQuality (QUALITY_BEST);

  // Perturb the cloud texture for more realism.
  module::Turbulence finalClouds;
  finalClouds.SetSourceModule (0, cloudBase);
  finalClouds.SetSeed (3);
  finalClouds.SetFrequency (16.0);
  finalClouds.SetPower (1.0 / 64.0);
  finalClouds.SetRoughness (2);

  // Given the water and cloud noise modules, create a non-seamless texture
  // map, a seamless texture map, and a spherical texture map.
  CreatePlanarTexture (finalWater, finalClouds, false, TEXTURE_HEIGHT,
    "textureplane.bmp");
  CreatePlanarTexture (finalWater, finalClouds, true, TEXTURE_HEIGHT,
    "textureseamless.bmp");
  CreateSphericalTexture (finalWater, finalClouds, TEXTURE_HEIGHT,
    "texturesphere.bmp");

  return 0;
}

void CreateTextureColorLayer1 (utils::RendererImage& renderer)
{
  // Create a water palette with varying shades of blue.
  renderer.ClearGradient ();
  renderer.AddGradientPoint (-1.00, utils::Color ( 48,  64, 192, 255));
  renderer.AddGradientPoint ( 0.50, utils::Color ( 96, 192, 255, 255));
  renderer.AddGradientPoint ( 1.00, utils::Color (255, 255, 255, 255));
}

void CreateTextureColorLayer2 (utils::RendererImage& renderer)
{
  // Create an entirely white palette with varying alpha (transparency) values
  // for the clouds.  These transparent values allows the water to show
  // through.
  renderer.ClearGradient ();
  renderer.AddGradientPoint (-1.00, utils::Color (255, 255, 255,   0));
  renderer.AddGradientPoint (-0.50, utils::Color (255, 255, 255,   0));
  renderer.AddGradientPoint ( 1.00, utils::Color (255, 255, 255, 255));
}

void CreatePlanarTexture (const module::Module& lowerNoiseModule,
  const module::Module& upperNoiseModule, bool seamless, int height,
  const char* filename)
{
  // Map the output values from both noise module onto two planes.  This will
  // create two two-dimensional noise maps which can be rendered as two flat
  // texture maps.
  utils::NoiseMapBuilderPlane plane;
  utils::NoiseMap lowerNoiseMap;
  utils::NoiseMap upperNoiseMap;
  plane.SetBounds (-1.0, 1.0, -1.0, 1.0);
  plane.SetDestSize (height, height);
  plane.EnableSeamless (seamless);

  // Generate the lower noise map.
  plane.SetSourceModule (lowerNoiseModule);
  plane.SetDestNoiseMap (lowerNoiseMap);
  plane.Build ();

  // Generate the upper noise map.
  plane.SetSourceModule (upperNoiseModule);
  plane.SetDestNoiseMap (upperNoiseMap);
  plane.Build ();

  // Given these two noise maps, render the lower texture map, then render the
  // upper texture map on top of the lower texture map.
  RenderTexture (lowerNoiseMap, upperNoiseMap, filename);
}

void CreateSphericalTexture (const module::Module& lowerNoiseModule, 
  const module::Module& upperNoiseModule, int height, const char* filename)
{
  // Map the output values from both noise module onto two spheres.  This will
  // create two two-dimensional noise maps which can be rendered as two
  // spherical texture maps.
  utils::NoiseMapBuilderSphere sphere;
  utils::NoiseMap lowerNoiseMap;
  utils::NoiseMap upperNoiseMap;
  sphere.SetBounds (-90.0, 90.0, -180.0, 180.0); // degrees
  sphere.SetDestSize (height * 2, height);

  // Generate the lower noise map.
  sphere.SetSourceModule (lowerNoiseModule);
  sphere.SetDestNoiseMap (lowerNoiseMap);
  sphere.Build ();

  // Generate the upper noise map.
  sphere.SetSourceModule (upperNoiseModule);
  sphere.SetDestNoiseMap (upperNoiseMap);
  sphere.Build ();

  // Given these two noise maps, render the lower texture map, then render the
  // upper texture map on top of the lower texture map.
  RenderTexture (lowerNoiseMap, upperNoiseMap, filename);
}

void RenderTexture (const utils::NoiseMap& lowerNoiseMap,
  const utils::NoiseMap& upperNoiseMap, const char* filename)
{
  // Create the color gradients for the lower texture.
  utils::RendererImage textureRenderer;
  CreateTextureColorLayer1 (textureRenderer);

  // Set up us the texture renderer and pass the lower noise map to it.
  utils::Image destTexture;
  textureRenderer.SetSourceNoiseMap (lowerNoiseMap);
  textureRenderer.SetDestImage (destTexture);
  textureRenderer.EnableLight (true);
  textureRenderer.SetLightAzimuth (135.0);
  textureRenderer.SetLightElev (60.0);
  textureRenderer.SetLightContrast (2.0);
  textureRenderer.SetLightColor (utils::Color (255, 255, 255, 0));

  // Render the texture.
  textureRenderer.Render ();

  // Create the color gradients for the upper texture.
  CreateTextureColorLayer2 (textureRenderer);

  // Set up us the texture renderer and pass the upper noise map to it.  Also
  // use the lower texture map as a background so that the upper texture map
  // can be rendered on top of the lower texture map.
  textureRenderer.SetSourceNoiseMap (upperNoiseMap);
  textureRenderer.SetBackgroundImage (destTexture);
  textureRenderer.SetDestImage (destTexture);
  textureRenderer.EnableLight (false);

  // Render the texture.
  textureRenderer.Render ();

  // Write the texture as a Windows bitmap file (*.bmp).
  utils::WriterBMP textureWriter;
  textureWriter.SetSourceImage (destTexture);
  textureWriter.SetDestFilename (filename);
  textureWriter.WriteDestFile ();
}
