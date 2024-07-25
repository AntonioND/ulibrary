#include <nds/registers_alt.h>

#include "ulib.h"

const int ul_circle_mask_size = 1380;
const int ul_logo_size = 2843;
const int ul_logo_base_size = 3059;
const int ul_logo_msk_size = 2024;

const unsigned long ul_circle_mask[] =		{
	0x38464947, 0x001d6139, 0x00f7001d, 0x24222400, 0x54848684, 0xb6b45456, 0x3c3e3cb4, 0x6c9c9e9c,
	0xcecc6c6e, 0x343234cc, 0x64949294, 0xc2c46462, 0x4c4a4cc4, 0x7cacaaac, 0xdadc7c7a, 0x2c2a2cdc,
	0x5c8c8e8c, 0xbebc5c5e, 0x444644bc, 0x74a4a6a4, 0xd6d47476, 0x3c3a3cd4, 0x6c9c9a9c, 0xcacc6c6a,
	0x545254cc, 0x84b4b2b4, 0xe2e48482, 0x242624e4, 0x5c8c8a8c, 0xbabc5c5a, 0x444244bc, 0x74a4a2a4,
	0xd2d47472, 0x343634d4, 0x64949694, 0xc6c46466, 0x4c4e4cc4, 0x7cacaeac, 0xdedc7c7e, 0x2c2e2cdc,
	0x0000e300, 0x00000013, 0x0000a800, 0x130000e2, 0x00000017, 0x00321800, 0x910007ee, 0x7c7c0092,
	0x00077000, 0x92000005, 0x007c0000, 0x00d8ff00, 0xff0007ff, 0x00ff0017, 0x00006d00, 0x92000005,
	0x007c0017, 0x00988500, 0x8100eae7, 0x007c0017, 0x003c0000, 0x1700e300, 0x00000013, 0x00486000,
	0x00000003, 0x01000000, 0x00808800, 0x2200e519, 0x00000013, 0x00189000, 0x1700ee79, 0x7c000091,
	0x00380000, 0x00000700, 0x7c000092, 0x00ff7e00, 0x0000ff00, 0xffc000ff, 0x00320000, 0x00000700,
	0x7c000092, 0x00abff00, 0xff0006ff, 0x7cff0092, 0x00ebff00, 0xff0006ff, 0x7cff0092, 0x003a0000,
	0x00002500, 0x7c000091, 0x00200000, 0x0000eb00, 0x00000013, 0x00000000, 0x17000000, 0x00000000,
	0x6073b800, 0x139e00e2, 0x0000805c, 0x7075d27c, 0x81e000e6, 0x007c174c, 0x006f9000, 0x17000079,
	0x00000067, 0x076f4a00, 0x810000e3, 0x007c005c, 0x00642000, 0x5000009b, 0x00000061, 0x00749000,
	0x01e00079, 0x00001761, 0x005c6c00, 0x00000000, 0x00000075, 0x00cdf400, 0x1300cbe1, 0x00000000,
	0x00d00000, 0x0000e300, 0x00000013, 0x0085f800, 0x13002bf7, 0x7c000083, 0x68001800, 0x919e00ee,
	0x007c8000, 0xff00707c, 0x92ff0005, 0x007cff00, 0x6000ffff, 0xff9e00ff, 0x00ff8000, 0x33296d7c,
	0x9200b705, 0x7c7c0093, 0x33704a00, 0x8000e0f4, 0x007c0017, 0x48340000, 0x17eb6400, 0x7c001383,
	0xffff0000, 0x00ffff00, 0xff00ffff, 0x000090ff, 0x17000079, 0x00000000, 0xfcb40000, 0x00e4e301,
	0x00001313, 0xd6340000, 0x00586400, 0x7c004c83, 0xdcf85700, 0x80e4f7f4, 0x007c1313, 0x7718e000,
	0x1330eee3, 0x7c004f91, 0x10009000, 0x17e5b779, 0x7c001393, 0x34ff1800, 0x9164ffee, 0xff7c83ff,
	0xbb70387c, 0x92e5e007, 0x007c1317, 0xcb34ff00, 0xffff64ff, 0x7cffff83, 0x88f8327f, 0x92e5e407,
	0x007c1313, 0x70e7ab00, 0x92e06406, 0x7c7c1783, 0x3488eb00, 0x92646406, 0x7c7c8383, 0x7001ac7c,
	0x17e000ea, 0x00001700, 0xcd319800, 0x17cb00ea, 0x00000030, 0x00000000, 0x00000000, 0x00000000,
	0x9d000200, 0x00ff0000, 0x00004700, 0x04f92100, 0x00000000, 0x00002c00, 0x001d0000, 0x0807001d,
	0x080100ff, 0x0010481c, 0x10101008, 0xb0c82c1e, 0x300841a1, 0x81402010, 0x040a0501, 0x74384030,
	0x06226208, 0x50282402, 0x00824120, 0x36108b81, 0x8288ec0e, 0x1c060500, 0x21100838, 0x92830593,
	0x64a86028, 0x048392f9, 0x68342a05, 0x0142a150, 0x3004064d, 0x02086c64, 0x1c120606, 0x6030a844,
	0x0f0b81c1, 0xd0581c2e, 0x09059460, 0x529d0da5, 0x6ac069f0, 0x52290888, 0xc0104824, 0x2c1156c5,
	0x082ce428, 0x09540501, 0x28240365, 0x8342a250, 0xb032050a, 0x05812add, 0x051a0401, 0x40c02476,
	0x11070682, 0xd1685432, 0xcb80c461, 0x08a44a2d, 0x088540e1, 0xd4014ba4, 0x42c2ab1d, 0x4603c908,
	0x61b158ac, 0x1d1182c5, 0x6008a42a, 0xc4578142, 0x36369d02, 0x894522e1, 0x1c36130e, 0xc0fc40b8,
	0x2a2d0986, 0xe1a17044, 0x4d948633, 0x6050b049, 0xe08b40ba, 0xd07c5e27, 0x8ac4e17e, 0xd0320d11,
	0x187c2eff, 0x02120221, 0x5048b854, 0x0382c061, 0x787fe3da, 0x87416070, 0x281c1102, 0x041e50e0,
	0x68020a0a, 0x03035eb0, 0x76c1706c, 0xdde76e08, 0xd0242500, 0x20240099, 0x22031756, 0x03429808,
	0x60903daa, 0x577c0f7c, 0x71cc0241, 0x100a0240, 0x07a0168c, 0x82305429, 0xb86dda81, 0x8e0f87e0,
	0x0153d078, 0x7bdbf642, 0x02f7c82f, 0x96640b7d, 0x22220a9f, 0xd40718b6, 0x75c25085, 0xe1a09c1b,
	0xb09c0f76, 0x8de100c1, 0x3052d867, 0x6f012630, 0x24970229, 0xb01c1771, 0x341d04c2, 0x220182e8,
	0x41960050, 0x82a071ff, 0xd0640103, 0xb00b7000, 0xb26c1ae6, 0x04816005, 0x1a10501c, 0xe0b25500,
	0xb5926418, 0x1d659a90, 0x0399b664, 0xc2c0081a, 0x37fd8a99, 0x557b5e5d, 0x250557e0, 0x03801608,
	0x8049e006, 0x07f9054e, 0x78165e20, 0x6a5ac210, 0x56421045, 0x173a682a, 0x59a43043, 0x65565521,
	0x0195a541, 0x4045c59e, 0xea396162, 0x181a5013, 0x78029430, 0x46eab57a, 0x5304baad, 0x6b240254,
	0xe1270513, 0x265393ba, 0x49537489, 0x92a9ed15, 0x444d4d62, 0x391845d1, 0x09a76d7b, 0x432deb85,
	0x3b000101
};

const unsigned long ul_logo[] =		{
	0x38464947, 0x00b26139, 0x00f70046, 0x04020400, 0x647c827c, 0x3e14fcc2, 0xc4824484, 0x143c423c,
	0xa254c45a, 0x646264d4, 0x44e4e2e4, 0xa2a4846e, 0x64422ca4, 0xc4c4bec4, 0xb25cc4c6, 0x3c3a3ce4,
	0x24a48244, 0x8234e466, 0xa4623cfc, 0x746c5244, 0xf2e47472, 0x949294fc, 0x2cfcc28c, 0xb254a456,
	0xe49a4cfc, 0xb4fca24c, 0x1e1cfcd2, 0xfcb2741c, 0x6c746654, 0x762c8472, 0x74523cec, 0x3c948a8c,
	0x722c5c52, 0xfce2c4d4, 0x3cfcaa54, 0xb2b48c56, 0x74462cb4, 0x24d4d2d4, 0x7644543a, 0xfcce8ca4,
	0x44fc923c, 0xbe649c7e, 0x2c2e2cf4, 0x8c746664, 0xc27c8c8a, 0x54423cfc, 0xa4946e34, 0x8e3ca49e,
	0x6c5e44ec, 0x1cfcfaf4, 0x7624b452, 0xf4eef4fc, 0x14f49a4c, 0x964c1416, 0xc46a2ccc, 0xd4acaeac,
	0x924cd4ca, 0xf47224bc, 0xe49c9a9c, 0xba7ce4de, 0x745a4cfc, 0x6cfcead4, 0x7234fcae, 0xfcd6a4b4,
	0x648c868c, 0x4a1cfcca, 0xdcae5c94, 0x446c6e6c, 0x4e2c8c72, 0x4c3a1c64, 0xf47c7a7c, 0xb26cf4f2,
	0xfca664fc, 0x24fcdaac, 0x7e742426, 0xd47a3484, 0x3cfcae54, 0x4e3c8c5e, 0x64361474, 0x74fcce9c,
	0x4e4c746e, 0xfc8a3c4c, 0x44645a54, 0x0a0cfc9a, 0x8482840c, 0x44fcc664, 0x5e1ccc8e, 0x6c666cd4,
	0x54eceaec, 0xa2ac846a, 0xccc6ccac, 0x44443a34, 0x7224b48a, 0xb4622cec, 0x947c726c, 0xca949c96,
	0xac521cfc, 0x5cfca64c, 0x7e347c6e, 0x745a2cec, 0x54dc661c, 0xbe645456, 0xbcbabcec, 0x34dcdadc,
	0x5a243436, 0xc49e54b4, 0x2cfcdec4, 0x4a2c9452, 0x544a447c, 0x2c84461c, 0x060cfc7e, 0xcc863c0c,
	0x1c444644, 0xa64ccc5e, 0xece6ecdc, 0x24ec6a1c, 0x624c2422, 0x9c8e8c7c, 0x24bcb6bc, 0xd6dc7c42,
	0xfcba5cdc, 0x1c343234, 0x72341c1a, 0xfcf6fcbc, 0x342c2a2c, 0x5e54945a, 0x5c5a5c6c, 0x446c462c,
	0xc69cac86, 0xdc6e2cfc, 0x1c947244, 0x4a2cbc56, 0xfc9e546c, 0x547c767c, 0x6e3c544e, 0xb4aeb48c,
	0x547c5a44, 0x6e6ce4ae, 0xec9a4c7c, 0x3cf4762c, 0x7224f48e, 0x9c4a1cfc, 0x34847e84, 0x6634dc7a,
	0x6c564ca4, 0x5cfcf6ec, 0xb67cfcb6, 0x847674fc, 0x94745634, 0xe6cc948e, 0x543e1cfc, 0x44a47a3c,
	0x6a6cfc96, 0xfcc68474, 0x2cfcfefc, 0xbe7cfc7a, 0xfceedcfc, 0xb4b4763c, 0x3a1cfcde, 0xfcd2a464,
	0x4c645e5c, 0x5624fc9e, 0x646664ac, 0x343c3e3c, 0x8e8cfc86, 0xd4ced48c, 0x9cbc964c, 0xb66c9c9e,
	0xfc8e3cfc, 0xac848684, 0xcaccaca6, 0xfcbe5ccc, 0xdcfcaa5c, 0xae5cfcea, 0xfccea4fc, 0x9cfcc66c,
	0xa6549c96, 0xfcbe84fc, 0x92e36406, 0x7c7c1783, 0x3488eb00, 0x92646406, 0x7c7c8383, 0x6001447c,
	0x18e30061, 0x00001700, 0xba313000, 0x18060061, 0x00000030, 0x00610000, 0x00000000, 0x00000013,
	0x9d000200, 0x00ff0000, 0x00004700, 0x04f92100, 0x00000000, 0x00002c00, 0x00b20000, 0x08070046,
	0x09e700ff, 0xa0b0481c, 0x130883c1, 0xb0c85c2a, 0x1087c3a1, 0x489c4a23, 0x8bc5a2b1, 0xdc6a3318,
	0xc7a3b1c8, 0x8a43208f, 0xa4b2491c, 0x532893c9, 0xb2c95caa, 0x3097cba5, 0x499cca63, 0x9bcda6b3,
	0xdcea7338, 0xcf8010a9, 0x0a83409f, 0xa8b44a1d, 0x9348a3d1, 0xb4ca5d2a, 0x50a7d3a9, 0x4a9d4aa3,
	0xabd5aab5, 0xc1088543, 0xd7abb5ca, 0x9cd750af, 0xc1a3a569, 0x1ad82337, 0x8ad1d034, 0x70b056d1,
	0x2a8dcae3, 0x39820684, 0x4de99294, 0xa82f8a06, 0x15297fbf, 0xede9d381, 0x1188c3dc, 0x62d24a47,
	0x8fbd0f6f, 0x0c00f6ff, 0x6d26cb58, 0xde6b1267, 0x8d92d5cc, 0xf3437bbc, 0xaff94c9d, 0xb4a02016,
	0x8a173214, 0x4cd7ebb3, 0x1049b085, 0xc8b271fa, 0x465348a0, 0x901405ad, 0x28e2a038, 0xb60966b9,
	0x6940e3f1, 0xba1d11cc, 0x17506eaf, 0xed3ef752, 0xeb9002fb, 0xdf202182, 0x37c69aee, 0x037db5e6,
	0x474251ff, 0xbf7112ad, 0x1ec75fad, 0x3a250807, 0x97cbb999, 0xdf5046bb, 0xb4b590da, 0x10025228,
	0x04806216, 0x570b8c48, 0x038de088, 0x20a1c409, 0x8129ee76, 0x7e107cc0, 0xe0680675, 0x1c851361,
	0x0931d839, 0xb8749c38, 0x10b487c1, 0x7e25c620, 0x82894264, 0xe298a494, 0xe844d426, 0x6c1055a2,
	0x090f5e02, 0x10c3c0d8, 0x63a380b2, 0xd06c9c87, 0xf6401863, 0xb1240411, 0x7b82d17c, 0x8098a8e2,
	0xe8bc9111, 0xc8425424, 0x7e265e08, 0x3806d1d8, 0xa1c95c6d, 0x106e1f8f, 0x747d1f64, 0x2c27c6a0,
	0x8a485114, 0x0d89a04a, 0xa9b64f0d, 0x800b1094, 0xa9378177, 0x96a592c8, 0x21f8f21c, 0x09801b90,
	0xec1d1aa6, 0x9b260a20, 0x25009024, 0xc0ba244a, 0x5a366e07, 0x305a1554, 0x32124407, 0x9dc52960,
	0xa3d8f63b, 0xd1f46197, 0xaa620769, 0xbb0c46a1, 0xa1c4a088, 0xc16a2689, 0xfab68e1a, 0xe0d81793,
	0x02cc97ff, 0xa599dc32, 0xc972998e, 0x86a09829, 0x78afc31a, 0xaa48517c, 0x0df2144a, 0xcab6ae9b,
	0x580d7806, 0x97964331, 0x8ea79962, 0x29d9025d, 0x91a8d298, 0x706a0c6d, 0x7a288dc3, 0x216890b4,
	0x4c22149b, 0x010a8eb2, 0x849b7304, 0x97148e00, 0x06eb8a62, 0xe7b2f8be, 0xd9842906, 0x8ed93481,
	0x7fb7831a, 0x024b00a8, 0x42db0ec3, 0x79b6e86b, 0x205fa48d, 0xd214ab62, 0xbd89c9e6, 0xafcaf2bb,
	0xeafcc61a, 0x54d635ad, 0x2026c572, 0x1249bb93, 0xa2fc26ac, 0xa6dc4610, 0xbc745f57, 0x10a5eef2,
	0x27299c43, 0x09c174ce, 0x91f6f990, 0xf4651402, 0xff372fe1, 0x1248dc72, 0x02dc82c3, 0xfc985e21,
	0xf5a284e2, 0xf02207e0, 0x8f2b8ada, 0x4e55e828, 0xdbe42918, 0x6d7a1741, 0x1cd07191, 0x230b523b,
	0xb20c8046, 0xed28a411, 0xa9f71462, 0xf115c85c, 0xc4f11bc6, 0xc1763c6d, 0xb0773932, 0x88c92f45,
	0xafce73ff, 0x4dc35831, 0x62288ed8, 0x602dd183, 0x10da8d73, 0x5f02b10a, 0x8362832a, 0x8cc7511d,
	0xe8c88767, 0x39978c35, 0x0a18f067, 0x383c68ac, 0xf0846fe1, 0x6c2d0b4d, 0x8c2c02d2, 0x0d1dce32,
	0x85a686eb, 0xbd4b2f09, 0xe8ce8723, 0xbcd60305, 0x1ed7a142, 0xb84e0b80, 0x418ca823, 0xb4d8ea48,
	0xae354df0, 0xcac67773, 0x40e281b7, 0x214b7108, 0xe67ab480, 0xd70dc3de, 0x22429076, 0xc5b2f4c9,
	0xff0fa3bf, 0x283a00c3, 0xcd8b7c8f, 0x640c7723, 0x4562c32b, 0xd96a58e5, 0x30e02fa1, 0x9c330c93,
	0x05f7a9f8, 0xd0151bfb, 0x0288e746, 0x5307e0fe, 0xb026c288, 0xb1d389b1, 0xe9c87da1, 0x83005ec6,
	0xccc00881, 0x1fbbf67a, 0x8c909a38, 0x6b4d600b, 0xc65cd0be, 0x6b08e7ca, 0x7c07f018, 0x12e243c8,
	0x400c0467, 0xc0e638f0, 0x70d85fcd, 0x2dc83684, 0xc65b1383, 0x2fa6b2e7, 0x1905e874, 0x01a123e4,
	0x83e16fff, 0x1bf0301a, 0x0bc05967, 0xe703a38d, 0xd90b2698, 0x72add788, 0x00290be5, 0x937919d0,
	0x06ba1946, 0xd01df336, 0xc6c0bc00, 0x04681a37, 0x35f12e25, 0x600bf03a, 0x6806e0be, 0xbe666cc9,
	0x60325cc8, 0x260e4590, 0x74047443, 0x707f01c4, 0xa28c030b, 0x86fc4881, 0x99c8cf19, 0x7246946b,
	0xfd61b0a6, 0x1821f666, 0x5a1a05e8, 0xec16c70b, 0x858e3e46, 0xe47a07ed, 0x70fc1f23, 0x31202316,
	0x4d748409, 0x07a90e00, 0x8a600819, 0x06d7a2d3, 0x0b97a186, 0xc311230c, 0x92df0618, 0xe56f01e1,
	0xb8b784f1, 0xf0be2e05, 0xe1d2310d, 0x2508dd1b, 0x9bd1a267, 0x0140acca, 0x15253a59, 0xf040043f,
	0xbf1965e8, 0x31095e12, 0x0e5cc7c9, 0xf48104a0, 0xb98419a4, 0xe6a00819, 0x0429a82f, 0x25794e23,
	0x17c8ec4e, 0x5e82da3d, 0x2698e966, 0x811a4140, 0x330164b3, 0x684acb99, 0xa0460162, 0x00e83603,
	0x6a6e1fff, 0x98df0bc6, 0x83ae6f4c, 0xaf5c0380, 0x47001b9c, 0xc8f09697, 0x06f4380c, 0x0a45f8cb,
	0x133c2546, 0x6f9ab09e, 0xbe5980a8, 0x20424bf1, 0x31889fcb, 0x39be74c7, 0x6f5c5787, 0x5ae29b66,
	0x2bd19632, 0x636cfd51, 0x3564cc25, 0x7e42916f, 0xe60e9122, 0xe7480c30, 0x0c4a0082, 0xc8263b14,
	0x55ab39d1, 0x22f85eb5, 0x56e2804c, 0xd329e525, 0x19e2de5c, 0x470b380b, 0x9d85501d, 0xd810c626,
	0xae7b8d48, 0xf0628183, 0xda5e5348, 0xc19cfe80, 0x32d95f2b, 0xa3d5166c, 0x0d100d53, 0x01d3e407,
	0x93415874, 0x22988aac, 0xd83d6750, 0xbe24c3f0, 0xf06da5da, 0x72a00bad, 0x3706e029, 0x91ee79b8,
	0x4320958f, 0x4fa9f826, 0xa740e807, 0x208b8d74, 0x389eb3da, 0xa9092250, 0xf6b55fb8, 0xf9313ba0,
	0x3b84a96a, 0x80912e60, 0x13e4600b, 0xc075701b, 0x188b2283, 0xb2875c42, 0xbd636288, 0x1ebbe5aa,
	0xa9032cff, 0x456012a3, 0x26518b0d, 0x708900ac, 0x200ac6fd, 0x9cb85acb, 0xd9bf0941, 0x312ea22a,
	0x2d62d984, 0x99f27d0c, 0x45e88360, 0x02a04a3e, 0x3e6d48b0, 0xe2882109, 0xed030626, 0x1a8a5151,
	0x703707e0, 0xfd485aea, 0xab42c6ec, 0x82063e0c, 0x8b387305, 0x00e01d5b, 0xbbd71061, 0x37c48960,
	0x255e23dc, 0x90042210, 0x02d69ce0, 0x4ea5afeb, 0x94b91953, 0xf0f418c4, 0x803a7e56, 0xefc1f110,
	0xa870ce61, 0x136252fe, 0x07017822, 0x9fadbc06, 0x8e027349, 0x90328650, 0xac5e0870, 0x9846ae00,
	0x27d8036f, 0x21b0c461, 0x9442684d, 0x8b171412, 0x0fa1a866, 0xf9702b17, 0x470ca1ac, 0x8b1a62dc,
	0xe95b8638, 0xd03a6290, 0x4e2d9837, 0x61ae108c, 0x4b153428, 0xc0689b09, 0x8bb1562c, 0x18c34820,
	0x1a17fe58, 0x09b1c0d0, 0x641a60fc, 0x5202c598, 0x04070dfb, 0x49c50312, 0x41cd92b2, 0xeb100489,
	0x209bc9f8, 0x50702e44, 0x027c0a01, 0x05d0270c, 0x81a0899e, 0x1661d452, 0x9125f8b0, 0x07629c8d,
	0x6a75a060, 0x0a377256, 0x8971e6e1, 0xf84a136c, 0x01723786, 0x628c5207, 0x05206914, 0x03a0b202,
	0xc8c59f33, 0x03407684, 0x44df706c, 0x550845cb, 0x219c1710, 0x25d43aad, 0xfe0f136e, 0xe9f31225,
	0xd8ab1449, 0xf536a502, 0x00d10c5c, 0xd1eb9171, 0x361d53aa, 0x3138908c, 0x6faa727a, 0xba11732d,
	0x7cd86bab, 0x008402c0, 0x9d5c1299, 0x4361e53c, 0x26cc818c, 0x02bccb47, 0xd9ad240b, 0x0d82f1c7,
	0x066c1d5c, 0x9e90118a, 0xe999b41c, 0x828f8c2b, 0xa85e391b, 0x41080ac2, 0x112373ec, 0x732cfbdb,
	0x05907426, 0x3e5bbf77, 0x35c04086, 0x6cbc708a, 0x4510837f, 0xaa3500c0, 0x6f7feb91, 0xf01f0847,
	0x20682182, 0x02184108, 0x40f85e02, 0xf1ce1dc3, 0xe3fc7b8e, 0x404a8f20, 0x003b0000
};

const unsigned long ul_logo_base[] =		{
	0x38464947, 0x00b26139, 0x00f70046, 0x04020400, 0x14b48e4c, 0xc66c843e, 0xcc924cfc, 0x3c94522c,
	0x621c443a, 0xacaeaccc, 0x54eceaec, 0x5654fcaa, 0x8c765c54, 0xd4948e94, 0x7a2cd4ce, 0xfc02fcfc,
	0x6c2c2a2c, 0x8e3c746e, 0xfcba5cfc, 0xc4ac6e3c, 0xded4c4be, 0xd47634ec, 0xfcb45624, 0x9ea4fcfa,
	0x6c563ca4, 0x8c4c4a44, 0x0000fcbe, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x04f92100, 0x00000000, 0x00002c00, 0x00b20000, 0x08070046,
	0x082100ff, 0xa0b0481c, 0x130883c1, 0xb0c85c2a, 0x1087c3a1, 0x489c4a23, 0x8bc5a2b1, 0xdc6a3318,
	0x47a3b1c8, 0x7a410600, 0x23f2491c, 0x13259380, 0x32b8248a, 0x1097cba5, 0x3984b657, 0x984d4213,
	0x1cb27338, 0x40a51328, 0xfa794091, 0xe81369b4, 0x7f47a2d0, 0x53c9949e, 0x4c9253a7, 0x2a9cfe89,
	0xa1d52835, 0xa4eea351, 0xd3e6f44a, 0x6a9716af, 0xacb20a0d, 0x915ca5d2, 0x94dad4fa, 0x70b059ab,
	0xdaccd631, 0xadc86ab5, 0xadb6e778, 0x452fb71b, 0xd2f76ebd, 0x20b81c15, 0x277eaf5b, 0x40d0d826,
	0x90c78182, 0x70683017, 0xb44de341, 0x45b28584, 0xe77312ca, 0x331388a4, 0x01c170d4, 0x53620883,
	0xc1208ea7, 0xa20d05c2, 0x8d8e864b, 0x0e8481d0, 0xcea2c5aa, 0x05b5800d, 0xce37b4d8, 0x41304e0e,
	0x3b62dd83, 0xc160d834, 0x16e68382, 0xbdc03036, 0xe265425a, 0xae2e5fd8, 0x8681208e, 0x7bc1e0ef,
	0x0090d7ff, 0x0dd4e381, 0xcecf001c, 0xea03a37e, 0x706c0d27, 0x7dbc3e30, 0x3b5fdeef, 0x801f00d8,
	0x05ed0401, 0xc8039188, 0x7d40d045, 0xe0a791f6, 0x57ee0a7d, 0x46028020, 0x1b069108, 0x821ac52c,
	0x60a83209, 0x7039f87e, 0x4a0752dc, 0x1a42a228, 0x06e16048, 0x5e2861df, 0xb7e1e378, 0x96300261,
	0x0b52c067, 0x8de23024, 0x94b03505, 0x7865ea01, 0x5dd005df, 0x437e2310, 0x7c2408c2, 0xa387ac12,
	0xd52e1484, 0x5a0b8a81, 0x1c034080, 0x0701d018, 0x58f0141c, 0xe0200c07, 0xda31915a, 0x4b9254b6,
	0x6ec0888a, 0xa3e6bc0b, 0x10541287, 0x28030100, 0x0a9cc140, 0x00413028, 0x1ad04802, 0x798a4298,
	0x06658412, 0x066ec178, 0x782299a8, 0x80195017, 0xe9cc0302, 0xd4149ca8, 0x1c9de759, 0x915f4030,
	0x94b7bc0e, 0x97b68103, 0x452702c0, 0x168263d0, 0x05001048, 0xa8da3403, 0x29ca74a3, 0x70159da9,
	0x9f4080ff, 0x60402646, 0x8a769ca8, 0xa14b021d, 0x0c62e098, 0xaaeaaa30, 0xaafa468f, 0x504c13a4,
	0xda426500, 0x2799eb6a, 0xaea4a035, 0x23305d89, 0x18b41200, 0xa6a706de, 0xacaa2dea, 0xb22c69d6,
	0x9d6ac276, 0xd89a7db3, 0xd2d4059b, 0xa36f63a6, 0xb780cb6e, 0x690aa2aa, 0xaa4c13b1, 0xa6cabe6f,
	0x167d2ce7, 0xbb412b5c, 0x9bb025a2, 0x4bcea4b4, 0xbae1bd6f, 0xc9bf2c7a, 0x7cc05b26, 0xda569409,
	0x4ae400bb, 0x67185c70, 0xa8c2db68, 0xab6e1aa6, 0x676bf2af, 0x80140fc4, 0x6b2c7d00, 0x71c6ed8a,
	0xc21d4069, 0x00c0260b, 0x5b130b9c, 0x9ee5b1ec, 0x0f04f11c, 0x0381c060, 0x6efcb1a5, 0xfcc23604,
	0x2719add5, 0xaac81a68, 0x05e73a32, 0xe75c9017, 0xfb941e05, 0x6c02b273, 0x16a67160, 0xa00116a0,
	0xa7a79907, 0x99e80b04, 0xa7690390, 0x6e6c368d, 0x06c12da3, 0xc008574a, 0x2a9a0993, 0xab3ab7f2,
	0xabe719ff, 0xf5b0526a, 0xd03f4003, 0x9699d101, 0xd3b62a06, 0x6a816412, 0x78f42303, 0xd6aa9c6a,
	0x2c1acc00, 0x0e7d708e, 0xdef39070, 0x62900e73, 0x89d6f9a4, 0x0384cf9f, 0x89b2f40d, 0x076efa67,
	0x80e41dd7, 0x9af109e5, 0x6fb4655a, 0x638cc0ec, 0xb740d827, 0xe8eb837c, 0xf07aafe8, 0x273e05dd,
	0x0f03f84b, 0xd15ad064, 0x719b400e, 0x46a81742, 0x36894176, 0x36f69cb0, 0xeeb746aa, 0x69f862a1,
	0x1ab321ce, 0x6f7eb1f8, 0x42f33aad, 0xa669973b, 0xbb2f7ed7, 0x78c109f7, 0x422066a8, 0xfbfe9de0,
	0x79236717, 0xff1a4bfe, 0x18a367f8, 0xfe800041, 0x0900a03b, 0x91fd90c8, 0xebb646c7, 0xc73ca900,
	0xed4d9d37, 0x572b7f3b, 0xbcc7928f, 0x6baf31c2, 0xba94cbef, 0xea90872e, 0x047ae6a5, 0xba589c59,
	0xe5b41a97, 0xbab90246, 0x239c52d6, 0x80258cc3, 0xce51a937, 0x00086a40, 0x76658a1a, 0x0dc8142d,
	0xaef729ff, 0x0108b124, 0xf059080c, 0xd38144e8, 0xc9452b1d, 0x3ef31e53, 0x59f79e98, 0x580b5de0,
	0xa76af59b, 0x50e1ca9a, 0x00824f35, 0xaea24ec6, 0x8bf10215, 0x0b6313f9, 0xfe809355, 0x6c020cbc,
	0x18058d4b, 0x05df2d10, 0x9bc26a00, 0x25c67e13, 0x4ca114a7, 0x1e6c1e75, 0x3af8430c, 0x210fd1ea,
	0xee0b13b6, 0x0d8087bc, 0x742c4dd8, 0x9f0e247b, 0x200da5d3, 0x449692e0, 0x23310a80, 0x51c4de49,
	0x14fb912c, 0x476846e5, 0x558f957a, 0x038ef814, 0x0d3c658e, 0x537d400c, 0x42f3a29c, 0x68f89fb8,
	0x990984f1, 0x42d5229c, 0x31948246, 0xe4e8105a, 0x98d32649, 0x8ce42942, 0x6e660a9b, 0x0b98e988,
	0x7e8df2fc, 0x4f268a5a, 0x4905abe2, 0x644a0080, 0x4744a398, 0xc079721a, 0xde53823b, 0x819962fa,
	0x53273da1, 0x21803376, 0x2ec88971, 0x240012f2, 0x213c1fc4, 0x1e19c890, 0x700b0364, 0x532a6f23,
	0xb093cfff, 0x849b20ab, 0x43cd33e6, 0xe03104cd, 0xd46ba08e, 0xc1995abd, 0x96077dab, 0x39994c81,
	0x08bb67df, 0x179212dc, 0xc50b0a5d, 0x00b3cf12, 0x58009fb3, 0xfa4040a0, 0x54814e45, 0x667810a4,
	0xccf7f516, 0x3eab4552, 0xc81df9de, 0x924dc61a, 0x3f3c92a5, 0x992c5e5b, 0x45b04b37, 0x581d24e7,
	0x49db4627, 0x947677b9, 0xe6139797, 0xb6885e41, 0xa94f4e80, 0xe4680906, 0xd350102e, 0x1a4171d4,
	0x12054068, 0x180a4a8a, 0x43546a8a, 0x19c73894, 0xca5802cb, 0x6a021e7d, 0x4b94ff46, 0xa3922cd5,
	0x49eb8186, 0x6a4c820b, 0x3f84c40e, 0x0d1b27a4, 0x388152a2, 0x5b7684f3, 0x60348b00, 0x3059f29e,
	0xcf023e52, 0xd3b9c52b, 0x8aa00a29, 0x1be971ce, 0x5ed7820f, 0x4676f171, 0xa0fe6b8d, 0xdaca904a,
	0x05752055, 0x73553f00, 0x35faa910, 0x8f8a5ea0, 0x00b348b6, 0x8fb2a1d0, 0x05d9aa87, 0x07d11706,
	0x00401cff, 0xcb9b025e, 0xd0904a8e, 0x6180c06e, 0x932e8082, 0xf0823909, 0xed7ba930, 0xe8e121ec,
	0x94a2614e, 0xd2f4a08e, 0x2b7a5a06, 0x0128bd51, 0xa41864d7, 0x0f4ad4ea, 0x1403d778, 0x18a4dac8,
	0xcadb58db, 0xd9cd9cea, 0x8aef0a0d, 0x15e8b146, 0xe471b9b3, 0x2ec35574, 0x886416e7, 0xf6c03162,
	0xfb29ca9c, 0x93984416, 0x5cccc0bc, 0xb8e91de4, 0x3d355596, 0xa9013856, 0x60729dd3, 0x90fce790,
	0x5edadaa8, 0x98516400, 0x0e0dd45e, 0x31a3600d, 0x0363449e, 0x7b856e81, 0x1aa2c6a8, 0x44388784,
	0x68c95640, 0x202d223f, 0x2af32374, 0xc5174879, 0x01f7963f, 0x73ec8b5d, 0x84d825d4, 0x0387133c,
	0xe8e5ea73, 0x5d6c54eb, 0x1bf2c507, 0xdc507188, 0xf922d343, 0x2f6e4b20, 0x23c76c80, 0xab48c122,
	0x029872c4, 0x28ae43f2, 0xcea77836, 0xae94b1d3, 0x75a55bc5, 0xb2ec9fa4, 0x6bae9fd6, 0xf8c5381b,
	0xa2fb78ff, 0x779997ed, 0x78e995db, 0xa7fb6203, 0x40f22d99, 0xb86cb523, 0x49e94e24, 0xe926046a,
	0x18551574, 0x6d82dad4, 0x8ab358dc, 0xdc1293f9, 0x3b4245f3, 0x52e88149, 0xa6ba98c5, 0x8093d4d5,
	0xc6cc41bf, 0x79c03db5, 0x83a52b23, 0x9e22fa49, 0xa840e92d, 0x0d4b80b3, 0xc01c02e9, 0x55f4c366,
	0x54ee2963, 0x8e7e76d4, 0x81171673, 0x221a9dc6, 0xb09ed1c6, 0x3d6c3d87, 0xbf37770b, 0x4ab3518d,
	0x419e28b5, 0xa564838c, 0xa3e60733, 0xf67eb4e3, 0x6ec13ad7, 0x6cad5c7c, 0xce2d5b66, 0xa8a29e72,
	0x296a43d3, 0xd8760751, 0xd2d30a7e, 0xb57fa614, 0x82fbd9a9, 0x99cb97f6, 0x2bab526b, 0x774e4902,
	0xafe6304e, 0x31aadb57, 0xfa972015, 0x72818d6c, 0xbabd06b6, 0xf49918c6, 0xf5cc94ed, 0x2aff658a,
	0x54b2a94d, 0xb6334fba, 0x0e627900, 0x284e13a9, 0x261c3294, 0xd7950d54, 0x7face62a, 0x1c4af15d,
	0x0600a8d0, 0x03818e56, 0x124abc14, 0x9b98adc8, 0x7f6de783, 0x032e2c1c, 0x665ac500, 0xa94dd6ab,
	0x1b4b6da9, 0xf089cfb5, 0xd8c85a2b, 0x320a7737, 0x882e8861, 0xd08ace23, 0xcb7a22b1, 0xa8e4012d,
	0xc970e938, 0x539c01b9, 0xf2d39e9a, 0x799f44eb, 0x363854f4, 0x9a25f7ac, 0xf41d69be, 0x47beeec0,
	0x87390a97, 0xb45fbb33, 0x822aa16d, 0x25bae11d, 0x146887f5, 0x0cc7b93b, 0x4d643501, 0xf08eef6e,
	0x37469e46, 0xc17bf221, 0x095f9f0e, 0x79e64034, 0x9001b9ff, 0x2a181bd3, 0xb01a383e, 0x10226aaa,
	0x602cc781, 0xfce18f01, 0xf9737f0b, 0x9f005cec, 0x046f6f94, 0xd2f7d394, 0xb73f67b3, 0x0c85bd49,
	0xbb1078e0, 0xf1a4423e, 0xfea297a9, 0x257fdb9a, 0x003b0020
};

const unsigned long ul_logo_msk[] =		{
	0x38464947, 0x00b26139, 0x00f70046, 0x04020400, 0xd4948e94, 0x4a44d4ce, 0xeceaec4c, 0x6cacaeac,
	0x2a2c746e, 0xfcfafc2c, 0xd4a49ea4, 0x5654ecde, 0xc4bec454, 0x3c8c765c, 0xfefc443a, 0xb23478fc,
	0x00088704, 0x770014d1, 0x01f25400, 0x130008e6, 0x0000000d, 0x0082f200, 0x0d000008, 0x00000000,
	0x00003c00, 0x130000e7, 0x00000000, 0x00001800, 0x910000ee, 0x007c0000, 0x644f7000, 0x92e9e505,
	0x777c13d3, 0xe302ff00, 0xffea00ff, 0x00009100, 0x1801007c, 0x00e90000, 0x00001300, 0x18000000,
	0x00000000, 0x00000000, 0x30849300, 0x920ee819, 0x007c8513, 0x82740000, 0x2300d000, 0x770000d1,
	0x00d97800, 0x17008b01, 0x770000d1, 0x0000c800, 0x0000f092, 0x7f0000fd, 0x4f840000, 0x17e5e800,
	0x0000d313, 0x745a2877, 0x13e988e5, 0x770013d1, 0xb7441700, 0xd1b7e89c, 0x00779213, 0xd52a687c,
	0x13b788e9, 0x770092d1, 0x2000187c, 0x919d00ee, 0x007c1800, 0x08f29000, 0x920008b6, 0x007cad0d,
	0xe000ff00, 0xff3000ff, 0x00ff8800, 0xd814867c, 0x922f00b6, 0x007c1900, 0x00019800, 0x920000b2,
	0x007c0000, 0x00000000, 0x17000000, 0x00000000, 0x18000900, 0x109d0003, 0x00001800, 0x0010eb00,
	0x92000006, 0x007c1700, 0x60010000, 0x009e0000, 0x00000100, 0x20000800, 0xad9d0000, 0x00001800,
	0x0001e000, 0x88000030, 0x007c1700, 0x80000000, 0x00e90000, 0x00001300, 0x0000b400, 0x130000e9,
	0x00000000, 0x00384d00, 0xd100e89d, 0x00771713, 0x8c007000, 0xd7e90002, 0x00771300, 0xabc80200,
	0x0037e87f, 0x00009213, 0xc767887c, 0x133704e7, 0x770092d4, 0x0830d97c, 0xb8068807, 0x770117d1,
	0x08ff2300, 0x0000ff04, 0xff00adff, 0x002a6000, 0xd100889d, 0x777700d1, 0x00c00000, 0x0000b400,
	0x770000d1, 0xc8000100, 0x00e90000, 0x00001300, 0xfd4f0000, 0x00fee500, 0x770080d3, 0x05f2007c,
	0x00ff0800, 0x0000800d, 0xd882007c, 0x002f0000, 0x00001900, 0x82007000, 0xd7fe0002, 0x00778000,
	0x0000027c, 0x0000007f, 0x00000000, 0x08440000, 0xd1000e00, 0x0077ad85, 0x09cbf200, 0x0d03b408,
	0x770000d1, 0x01b2f200, 0x0d000808, 0x00000014, 0x98181800, 0x37e9e954, 0x00001313, 0xf800d000,
	0x13f700e7, 0x00001300, 0xf8012300, 0x09f70036, 0x005b1300, 0xa800f200, 0x0d9a0008, 0x00008300,
	0x08ac017c, 0x00ffe800, 0x00008013, 0xff00007c, 0x00ff0000, 0x0000ff00, 0x05f800ff, 0x00fff700,
	0x00008013, 0x5467f27c, 0x0dec0408, 0x770041d4, 0x88d04f00, 0xd3e3b4e5, 0x777717d1, 0x82ff2900,
	0x09feff4e, 0xff5b80ff, 0x23cbf27c, 0x0d04b408, 0x770000d1, 0x58bd0200, 0x00d6da00, 0x7700d1d1,
	0x2f304f77, 0xd3fc0ee5, 0x00778085, 0x04f9217c, 0x00000000, 0x00002c00, 0x00b20000, 0x08070046,
	0x081f00ff, 0xa0b0481c, 0x130883c1, 0xb0c85c2a, 0x1087c3a1, 0x489c4a23, 0x8bc5a2b1, 0xdc6a3318,
	0x47a3b1c8, 0x7a410600, 0x23f2491c, 0x13259380, 0x32b8248a, 0x1097cba5, 0x3984b657, 0x984d41f3,
	0x1cb27338, 0x40a51328, 0xfa794091, 0xe81369b4, 0x7f47a2d0, 0x53c9949e, 0x4c9253a7, 0x2a9cfe89,
	0xa1d52835, 0xa4eea351, 0xd3e6f44a, 0x6a9716af, 0xacb20a0d, 0x915ca5d2, 0x94dad4fa, 0x70b059ab,
	0xdaccd631, 0xadc86ab5, 0xadb6e778, 0x452fb71b, 0xd2f76ebd, 0x20b81c15, 0x277eaf5b, 0xc0104812,
	0x90c78380, 0xa0083417, 0xb44de340, 0x45b28584, 0xe77312ca, 0x331388a4, 0x4040a044, 0x53620383,
	0x80603ea7, 0xa2040281, 0x8d8e864b, 0x01818050, 0x66e773aa, 0xed3600cd, 0x137fb38d, 0xb5001024,
	0x59aae3ee, 0xfcce1657, 0xd0e462e5, 0xe010078f, 0x8df5b9bb, 0xdf477002, 0x8141daae, 0x0a31e0eb,
	0xbdce30ff, 0xdf03d2fc, 0x8887abc3, 0xf7f98120, 0x581003a9, 0x02215f4f, 0x2ff3f003, 0xbebf305d,
	0xe801827f, 0x06002027, 0x7adff754, 0x60380ded, 0x57d20781, 0xe60a7900, 0xea834097, 0x84610029,
	0xe14009f9, 0x802c0475, 0x680782a1, 0x057321b8, 0x0061187c, 0x98988e06, 0x08980e02, 0xd22a0322,
	0x0a8ba016, 0x68a3101a, 0x63485c04, 0x35fa3786, 0xf60b8ee3, 0xda021718, 0x01e02901, 0xd4f909cb,
	0x880e4678, 0x1805429e, 0x0b01a520, 0x00909948, 0x25495655, 0x69525a6c, 0xba4284c0, 0x2982e4d7,
	0x6a80c412, 0x66742236, 0x16aa1a6a, 0x78089080, 0x0380a638, 0x00906924, 0x6254266e, 0xd9e5956a,
	0xce2d00a3, 0x0788a029, 0x8c1aa029, 0xc0102908, 0xa7c98ca2, 0xde6049d6, 0x02a0a788, 0x6aa77a46,
	0x40441696, 0xf7f4087f, 0x6e6f0028, 0x9ea6c0fa, 0xa76a240a, 0xea6a89c3, 0x8a8ea47c, 0x3ea9aa2a,
	0xaaeb00ff, 0xaa7422a5, 0x9a527ba8, 0x62899bdf, 0x629c909a, 0x951a99f5, 0x622019b9, 0x00314ba0,
	0x100258a8, 0xbc00ddb0, 0x49ec803e, 0xa93b4eca, 0xcb3a6958, 0xbeba8fe6, 0xaa95c0b7, 0x9ad077a5,
	0x9c8a7ecc, 0x4b71f303, 0x5c046aa0, 0xeaaf1d1b, 0x011a97e2, 0x102812d3, 0xd031a996, 0x0df9b740,
	0xa9a19090, 0x40a65015, 0x6c252eb9, 0x9014096a, 0x7d629880, 0x0271f0c7, 0x0170abe8, 0x005c270a,
	0xac3d98b0, 0x9ad8be1b, 0xb600318a, 0x039f0bf1, 0x109c22e0, 0x9a7f06b9, 0x2ef240a6, 0x27c6a6f5,
	0x0398d64d, 0xe6ca5e76, 0x20033003, 0xb40a63b3, 0x219a527c, 0xc8b1fc37, 0x6bdc91d1, 0xd6aa7ac0,
	0x89867c66, 0xd4c166f5, 0x02c0941e, 0x19572245, 0x4a2000d4, 0xfb40c7d0, 0x4494400c, 0xc940779b,
	0x904a6562, 0xe7cd27bb, 0x3d2766a7, 0x5841aecd, 0xd621a723, 0xf5e03eb5, 0xcd7aa3b7, 0x2361d780,
	0xd1efe7ff, 0xf37d270d, 0x8db567da, 0x15076ab3, 0x1ad0e54b, 0xd7107cc2, 0xb1f02902, 0xf7737d69,
	0x7f6841f7, 0x076ab27d, 0xe7b4dcbb, 0x79941774, 0x1b9700a4, 0x4777417a, 0x95c2b5ee, 0x41b2b76f,
	0xf6652fa5, 0x6e775840, 0x3b8667f8, 0x90ec505e, 0xd5f9940e, 0xf9041b88, 0x8c079203, 0x45baeb72,
	0xadd9736b, 0xf1e1aa92, 0x504cab20, 0x4dbf2fbd, 0x4400ef10, 0xd6e3799a, 0xb62fb413, 0xb6003005,
	0x88eaca58, 0x4780e07c, 0xe6ed40f7, 0xdf009c2e, 0xab5cc230, 0x103962b6, 0x1f8c6300, 0x3941af3e,
	0xd540ac6f, 0x884b13e7, 0x6f9db736, 0x02696cc1, 0x1eba0e3c, 0x15e8aea0, 0x81dc7be4, 0x35090351,
	0xac08ee3d, 0xc0040181, 0x32c60602, 0x6868d8ee, 0xd0d43a6f, 0x7a9cb408, 0xc420cf65, 0x20d66131,
	0xa5d9c267, 0x89df3a30, 0xa795005b, 0x0d4091a4, 0xa0ca2c46, 0xc356b500, 0x548a748a, 0xc45769a5,
	0x41d5f2c5, 0x00649e1d, 0x43e1ec1c, 0x81310732, 0x347cef40, 0xb044a254, 0x008144d7, 0x48077910,
	0x421b14a2, 0xf179459c, 0x21e45f8b, 0xb7d7cc03, 0x25d16dd9, 0xdf5be004, 0x25c674ea, 0x075f9191,
	0x5d1b6330, 0x31914182, 0x894e8e68, 0x8816eb53, 0x2f14a7c7, 0x60a00e6c, 0x1d92751f, 0x87801da2,
	0x130a7483, 0x811e4481, 0x852e1225, 0x1e93d4a4, 0xeda09719, 0x10033c88, 0x92bf2524, 0xa02d31c6,
	0x0b049b66, 0x42a00a02, 0x942a3910, 0x87cd3a38, 0x5449a358, 0x940105f6, 0x5c6f51ab, 0x4c051cd9,
	0x81bb8ded, 0xc9692816, 0x6fbc011c, 0x803c6400, 0x1d300c03, 0x3487fa5e, 0xf8988802, 0x654cc018,
	0x5f98c6bd, 0x3b000809
};

#define FIX(x)		((x) << 8)
#define UNFIX(x)	((x) >> 8)

int ul_splash1_fade;
int ul_splash1_fadeDir;

void ul_splash1_applyMask(UL_IMAGE *img, UL_IMAGE *msk)			{
   int i, j;
   for (j=0;j<img->sizeY;j++)			{
      for (i=0;i<img->sizeX;i++)			{
         int pixSrc = ulGetImagePixel(img, i, j), pixMsk = ulGetImagePixel(msk, i, j);
         pixMsk = 7 - ((pixMsk & 0x1f) >> 2);
			//Normally it should be that    	
//         pixSrc = (pixSrc & 0x1f) | pixMsk << 5;
			//But we will set every non transparent pixel to black
			if (pixMsk != 7)
				//For the PNG
//				pixSrc = 16 | pixMsk << 5;
				//For the GIF
				pixSrc = 31 | pixMsk << 5;
			else
				pixSrc |= 7 << 5;
         ulSetImagePixel(img, i, j, pixSrc);
      }
   }
}

UL_IMAGE *ul_splash1_createCircle(UL_IMAGE *img)			{
   int i, j;
   UL_IMAGE *dst;
   dst = ulCreateImage(img->sizeX, img->sizeY, UL_IN_RAM, UL_PF_PAL3_A5, 8);
   ((u16*)dst->palette)[1] = RGB15(31, 31, 31);
   for (j=0;j<img->sizeY;j++)			{
      for (i=0;i<img->sizeX;i++)			{
         int pixMsk = (ulGetImagePixel(img, i, j) & 0x1f) - 4;
         ulSetImagePixel(dst, i, j, 1 | pixMsk << 3);
      }
   }
   ulDeleteImage(img);
   return dst;
}

   
UL_IMAGE *ul_splash1_createMaskedImage(UL_IMAGE *msk, int x, int y)			{
   int i, j;
   UL_IMAGE *img;

   img = ulCreateImage(256, 192, UL_IN_RAM, UL_PF_PAL3_A5, 8);
   ((u16*)img->palette)[1] = RGB15(31, 31, 31);

	//Tout d'abord, remplir de blanc
   for (j=0;j<img->sizeY;j++)
      for (i=0;i<img->sizeX;i++)
      	ulSetImagePixel(img, i, j, 1 | 31 << 3);

	//Ensuite, y dessiner le sprite      	
   for (j=0;j<msk->sizeY;j++)			{
      for (i=0;i<msk->sizeX;i++)			{
         int pixMsk = ulGetImagePixel(msk, i, j) & 0x1f;
         ulSetImagePixel(img, x + i, y + j, 1 | pixMsk << 3);
      }
   }
   return img;
}

void ul_splash1_handleFade()			{
	ul_splash1_fade = ulMin(ulMax(ul_splash1_fade + ul_splash1_fadeDir, 0), 31);
	if (ul_splash1_fade == 0)
		ul_splash1_fadeDir = 0;
	if (ul_keys.pressed.value & (UL_KEY_A|UL_KEY_B|UL_KEY_START|UL_KEY_TOUCH))
		ul_splash1_fadeDir = 1;
}

void ul_splash1_drawFade()			{
	if (ul_splash1_fade > 0)			{
		ulSetAlpha(UL_FX_ALPHA, ul_splash1_fade, 3);
		ulDrawFillRect(0, 0, 256, 192, 0);
	}

	//ul_splash1_fade the second screen at the same time...
	SUB_BLEND_Y = ul_splash1_fade;
}

int ul_splash1_fadeTerminated()			{
   return (ul_splash1_fade >= 31 && ul_splash1_fadeDir == 1);
}   
   
void ul_splash1_drawBackText()			{
   const char *string = "http://brunni.dev-fr.org";
   ulSetTextColor(RGB15(31, 31, 31));
   ulDrawString((SCREEN_WIDTH - ulGetStringWidth(string)) / 2, SCREEN_HEIGHT - ul_curFont->charHeight, string);

	string = "For more information, please visit";
   ulSetTextColor(RGB15(31, 31, 0));
   ulDrawString((SCREEN_WIDTH - ulGetStringWidth(string)) / 2, SCREEN_HEIGHT - ul_curFont->charHeight * 2, string);
}

void ul_splash1_fillSecondScreen()			{
   int i;
   
   //Activate the second screen
	videoSetModeSub(MODE_5_2D | DISPLAY_BG2_ACTIVE);
	SUB_BG2_CR = BG_BMP16_256x256;
	SUB_BG2_XDX = 256;
	SUB_BG2_XDY = 0;
	SUB_BG2_YDX = 0;
	SUB_BG2_YDY = 256;
	SUB_BG2_CY = 0;
	SUB_BG2_CX = 20;
	
	//Initially black
	SUB_BLEND_CR = BLEND_FADE_BLACK | BLEND_SRC_BG2;
	SUB_BLEND_Y = 0x1f;

	//Hide the 3D screen as well
	BLEND_CR = BLEND_FADE_BLACK | BLEND_SRC_BG0;
	BLEND_Y = 0x1f;

	lcdSwap();
	vramSetBankC(VRAM_C_LCD);

	//Do 2 times the render to be sure the DS will understand it (>_<)
	for (i=0;i<2;i++)			{
		ulStartDrawing2D();
		ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 8), RGB15(0, 0, 8), RGB15(0, 0, 24), RGB15(0, 0, 24));
		ul_splash1_drawBackText();
		ulEndDrawing();
		ulSyncFrame();
	}

	//Capture and wait it to finish (next VBlank)
	REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3) | 1<<24;			// Captures to LCD bank C - 1<<24 to capture only 3D, not fading and so on
	swiWaitForVBlank();

	//Empty the main screen
	ulStartDrawing2D();
	ulEndDrawing();
	ulSyncFrame();
	lcdSwap();

	//Set this bank for use with the second screen
	vramSetBankC(VRAM_C_SUB_BG);

	//Show 3D again
	BLEND_CR = 0;
	BLEND_Y = 0;
	
	//Console (second screen) is no more valid after that...
	ul_isConsoleInited = 0;
}
   
//Returns 0 on error
/*
	ulInit(UL_INIT_ALL);
	ulInitGfx();
	should have been done before. Nothing should be loaded in memory as this splash uses about 125 kB of video memory (!) out of 128 kB.
*/
int ulShowSplashScreen1()
{	
	UL_IMAGE *imgLogo = NULL, *imgLogoMask = NULL, *imgFrame = NULL, *imgCircle = NULL, *imgLogoSub = NULL;
	int success = 0;
	
	ulInitText();

	//Do something with the second screen...
	ul_splash1_fillSecondScreen();
	
   int oldSource = ulGetLoadUtilitySource();
   ulSetLoadUtilitySource(VF_MEMORY);
   	
	ulSetTransparentColor(RGB15(31, 0, 31));
	
	int xLogoFix, yLogoFix;
	int zoom = FIX(64);
	int zoomSpeed = FIX(5);
	
	//Pour la premi�re partie
   imgLogoMask = ulLoadImageFileGIF((const char*)ul_logo_msk, (int)ul_logo_msk_size, UL_IN_RAM, UL_PF_5551);
   imgLogoSub = ulLoadImageFileGIF((const char*)ul_logo_base, (int)ul_logo_base_size, UL_IN_RAM, UL_PF_PAL5_A3);
   
   if (!imgLogoMask || !imgLogoSub)
   	goto cleanup;
	
	ul_splash1_applyMask(imgLogoSub, imgLogoMask);
	//Fin premi�re partie
	
	//Pour la deuxi�me partie
   imgLogo = ulLoadImageFileGIF((const char*)ul_logo, (int)ul_logo_size, UL_IN_RAM, UL_PF_PAL8);
   imgCircle = ulLoadImageFileGIF((const char*)ul_circle_mask, (int)ul_circle_mask_size, UL_IN_RAM, UL_PF_5551);

   if (!imgLogo || !imgCircle)
   	goto cleanup;

	xLogoFix = (SCREEN_WIDTH - imgLogo->sizeX) / 2;
	yLogoFix = (SCREEN_HEIGHT - imgLogo->sizeY) / 2;
	
	//Create an image using the mask data
	imgFrame = ul_splash1_createMaskedImage(imgLogoMask, xLogoFix, yLogoFix);
	imgCircle = ul_splash1_createCircle(imgCircle);	
	//Fin deuxi�me partie
		
   if (!imgFrame || !imgCircle)
   	goto cleanup;
   	
	//Copie les images en m�moire vid�o une fois pour toute
	ulRealizeImage(imgLogoMask);
	ulRealizeImage(imgLogoSub);
	ulRealizeImage(imgLogo);
	ulRealizeImage(imgCircle);
	ulRealizeImage(imgFrame);
	
	ulDisableTransparentColor();
	
	//Memory usage now: 125856 bytes (nearly the full VRAM)
	ul_splash1_fade = 31;
	ul_splash1_fadeDir = -1;

	ulImageSetRotCenter(imgLogoSub);
	imgLogoSub->x = SCREEN_WIDTH / 2;
	imgLogoSub->y = SCREEN_HEIGHT / 2;
		
	while(zoom > FIX(1) && !ul_splash1_fadeTerminated())
	{
	   ulReadKeys(0);
		
		ulStartDrawing2D();
				
		imgLogoSub->stretchX = (zoom * imgLogoSub->sizeX) >> 8;
		imgLogoSub->stretchY = (zoom * imgLogoSub->sizeY) >> 8;
				
		ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 24), RGB15(0, 0, 8), RGB15(0, 0, 8));
		
		ulDrawImage(imgLogoSub);			
		
		//Pour le fade, un simple rectangle plein transparent...
		ul_splash1_drawFade();
		
		ulEndDrawing();
		ulSyncFrame();
		
		if (!ul_keys.held.L)			{
			zoomSpeed += 104;
			zoom -= zoom / UNFIX(zoomSpeed);
			//Ne pas descendre en dessous de 1
			zoom = ulMax(zoom, FIX(1));
			
			ul_splash1_handleFade();
		}
	}
			
	imgCircle->stretchX = 55;
	imgCircle->stretchY = 35;
//	ulSetImageTint(imgCircle, RGB15(31, 31, 0));
	
	int x = (SCREEN_WIDTH - imgLogo->sizeX) / 2;
	int y = (SCREEN_HEIGHT - imgLogo->sizeY) / 2;
	int lightX = 60 - 100 - imgCircle->stretchX, lightY = (SCREEN_HEIGHT - imgCircle->stretchY + 10) / 2;
	
	while(lightX < 300 && !ul_splash1_fadeTerminated())
	{
	   ulReadKeys(0);
			   
		ulStartDrawing2D();
		
		if (!ul_keys.held.L)			{
			lightX += 3;
			ul_splash1_handleFade();
		}

		imgFrame->tint1 = imgFrame->tint2 = RGB15(0, 0, 24);
		imgFrame->tint3 = imgFrame->tint4 = RGB15(0, 0, 8);

		ulSetAlpha(UL_FX_DEFAULT, 0, 0);
		//Dessine d'abord le library
		ulSetImageTile(imgLogo, 60, 0, imgLogo->sizeX, imgLogo->sizeY);
		ulDrawImageXY(imgLogo, x + 60, y);
		
		//Puis la lumi�re par dessus
		ulDrawImageXY(imgCircle, lightX, lightY);
		//Et aussi sur le powered
		ulDrawImageXY(imgCircle, lightX - 20, lightY - 33);
		
		//Puis le � (pas cach� par la lumi�re)
		ulSetImageTile(imgLogo, 0, 0, 60, imgLogo->sizeY);
		ulDrawImageXY(imgLogo, x, y);
		
		//Pour que la DS veuille bien blender la frame et le cercle de lumi�re
		ulSetAlpha(UL_FX_ALPHA, 31, 1);
		ulDrawImage(imgFrame);

		ul_splash1_drawFade();
		
		ulEndDrawing();
		ulSyncFrame();

	}
	
	int angle = 0;
	//Begin fading to black
	ul_splash1_fadeDir = 1;
			
	while(!ul_splash1_fadeTerminated())
	{
	   ulReadKeys(0);
			   
		ulStartDrawing2D();
		
		imgLogoSub->stretchX = (zoom * imgLogoSub->sizeX) >> 8;
		imgLogoSub->stretchY = (zoom * imgLogoSub->sizeY) >> 8;
		imgLogoSub->angle = angle;
		
		ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 24), RGB15(0, 0, 8), RGB15(0, 0, 8));
		ulDrawImage(imgLogoSub);
		
		
		//Pour le fade, un simple rectangle plein transparent...		
		ul_splash1_drawFade();
						
		ulEndDrawing();
		ulSyncFrame();
		
		if (!ul_keys.held.L)			{
			angle -= 4;
			zoom -= zoom / 16;
			ul_splash1_handleFade();
		}
	}
	
	//If we've run until there, there was no error
	success = 1;
	
cleanup:
	//Clean up
	if (imgLogoSub)
		ulDeleteImage(imgLogoSub);
	if (imgLogoMask)
		ulDeleteImage(imgLogoMask);
	if (imgLogo)
		ulDeleteImage(imgLogo);
	if (imgCircle)
		ulDeleteImage(imgCircle);
	if (imgFrame)
		ulDeleteImage(imgFrame);
	
	//Restore the old source
   ulSetLoadUtilitySource(oldSource);
  	return success;
}


