xof 0303txt 0032
Material ground_water_MAT {
	1.000000;1.000000;1.000000;1.000000;;
	0.000000;
	0.000000;0.000000;0.000000;;
	0.000000;0.000000;0.000000;;
	TextureFilename {
		"stage_tex.jpg";
	}
}
Frame water_21_GEO {
	FrameTransformMatrix {
		1.000000,0.000000,0.000000,0.000000,
		0.000000,1.000000,0.000000,0.000000,
		0.000000,0.000000,1.000000,0.000000,
		0.000000,0.000000,0.000000,1.000000;;
	}
	Mesh {
		4;
		-5.000000;-30.000000;5.000000;,
		5.000000;-30.000000;5.000000;,
		5.000000;-20.000000;15.000000;,
		-5.000000;-20.000000;15.000000;;
		2;
		3;0,2,1;,
		3;0,3,2;;
		MeshNormals {
			4;
			0.000000;0.707107;-0.707107;,
			0.000000;0.707107;-0.707107;,
			0.000000;0.707107;-0.707107;,
			0.000000;0.707107;-0.707107;;
			2;
			3;0,2,1;,
			3;0,3,2;;
		}
		MeshTextureCoords {
			4;
			0.937700;0.682375;,
			0.953100;0.682375;,
			0.953100;0.666975;,
			0.937700;0.666975;;
		}
		MeshMaterialList {
			1;
			2;
			0,
			0;
			{ground_water_MAT}
		}
	}
}
AnimationSet Take_001 {
}
