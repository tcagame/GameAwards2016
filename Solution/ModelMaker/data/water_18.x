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
Frame water_18_GEO {
	FrameTransformMatrix {
		1.000000,0.000000,0.000000,0.000000,
		0.000000,1.000000,0.000000,0.000000,
		0.000000,0.000000,1.000000,0.000000,
		0.000000,0.000000,0.000000,1.000000;;
	}
	Mesh {
		6;
		5.000000;-20.000000;-15.000000;,
		15.000000;-20.000000;-15.000000;,
		5.000000;-30.000000;-5.000000;,
		5.000000;-30.000000;-5.000000;,
		15.000000;-20.000000;-15.000000;,
		15.000000;-20.000000;-5.000000;;
		2;
		3;0,2,1;,
		3;3,5,4;;
		MeshNormals {
			6;
			0.000000;0.707107;0.707107;,
			0.000000;0.707107;0.707107;,
			0.000000;0.707107;0.707107;,
			-0.707107;0.707107;-0.000000;,
			-0.707107;0.707107;-0.000000;,
			-0.707107;0.707107;-0.000000;;
			2;
			3;0,2,1;,
			3;3,5,4;;
		}
		MeshTextureCoords {
			6;
			0.953100;0.713175;,
			0.968500;0.713175;,
			0.953100;0.697775;,
			0.953100;0.697775;,
			0.968500;0.713175;,
			0.968500;0.697775;;
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
