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
Frame water_20_GEO {
	FrameTransformMatrix {
		1.000000,0.000000,0.000000,0.000000,
		0.000000,1.000000,0.000000,0.000000,
		0.000000,0.000000,1.000000,0.000000,
		0.000000,0.000000,0.000000,1.000000;;
	}
	Mesh {
		6;
		-15.000000;-20.000000;5.000000;,
		-5.000000;-30.000000;5.000000;,
		-15.000000;-20.000000;15.000000;,
		-15.000000;-20.000000;15.000000;,
		-5.000000;-30.000000;5.000000;,
		-5.000000;-20.000000;15.000000;;
		2;
		3;0,2,1;,
		3;3,5,4;;
		MeshNormals {
			6;
			0.707107;0.707107;-0.000000;,
			0.707107;0.707107;-0.000000;,
			0.707107;0.707107;-0.000000;,
			0.000000;0.707107;-0.707107;,
			0.000000;0.707107;-0.707107;,
			0.000000;0.707107;-0.707107;;
			2;
			3;0,2,1;,
			3;3,5,4;;
		}
		MeshTextureCoords {
			6;
			0.922300;0.682375;,
			0.937700;0.682375;,
			0.922300;0.666975;,
			0.922300;0.666975;,
			0.937700;0.682375;,
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
