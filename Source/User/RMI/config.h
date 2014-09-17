/******************************************/
/* Synaptics Design Studio 4     3.0.0.58 */
/*    10/21/2011 11:53:39 PM              */
/******************************************/


/**** Device Information ****/
#define FW_REVISION               "DS4 R3.0"   	/*  F01 Firmware ProductID  */
#define TOUCH_CONTROLLER          "S3200-I2C"  	/*  F01 PackageID  */
#define CONFIG_ID                 "QMAO"       	/*  F34 Configuration ID  */


/**** Register names ****/
#define F34_FLASH_CTRL00_00       0x0058  /*  Customer Defined Config ID 0  */
#define F34_FLASH_CTRL00_01       0x0059  /*  Customer Defined Config ID 1  */
#define F34_FLASH_CTRL00_02       0x005A  /*  Customer Defined Config ID 2  */
#define F34_FLASH_CTRL00_03       0x005B  /*  Customer Defined Config ID 3  */
#define F01_RMI_CTRL00            0x005C  /*  Device Control  */
#define F01_RMI_CTRL01_00         0x005D  /*  Interrupt Enable 0  */
#define F01_RMI_CTRL02            0x005E  /*  Doze Period  */
#define F01_RMI_CTRL03            0x005F  /*  Doze Wakeup Threshold  */
#define F01_RMI_CTRL05            0x0060  /*  Extended Wait Before Doze  */
#define F01_RMI_CTRL06            0x0061  /*  I2C Control  */
#define F01_RMI_CTRL08            0x0062  /*  Attention Control  */
#define F11_2D_CTRL00             0x0063  /*  2D Report Mode  */
#define F11_2D_CTRL01             0x0064  /*  2D Palm Detect  */
#define F11_2D_CTRL02             0x0065  /*  2D Delta-X Thresh  */
#define F11_2D_CTRL03             0x0066  /*  2D Delta-Y Thresh  */
#define F11_2D_CTRL04             0x0067  /*  2D Velocity  */
#define F11_2D_CTRL05             0x0068  /*  2D Acceleration  */
#define F11_2D_CTRL06             0x0069  /*  2D Max X Position (7:0)  */
#define F11_2D_CTRL07             0x006A  /*  2D Max X Position (11:8)  */
#define F11_2D_CTRL08             0x006B  /*  2D Max Y Position (7:0)  */
#define F11_2D_CTRL09             0x006C  /*  2D Max Y Position (11:8)  */
#define F11_2D_CTRL20             0x006D  /*  2D Pen Enable  */
#define F11_2D_CTRL21             0x006E  /*  Z Pen Lower Threshold  */
#define F11_2D_CTRL29             0x006F  /*  Z Touch Threshold  */
#define F11_2D_CTRL30             0x0070  /*  Z Touch Hysteresis  */
#define F11_2D_CTRL31             0x0071  /*  Small Z Threshold  */
#define F11_2D_CTRL32_00          0x0072  /*  Small Z Scale Factor  */
#define F11_2D_CTRL32_01          0x0073  /*  Small Z Scale Factor  */
#define F11_2D_CTRL33_00          0x0074  /*  Large Z Scale Factor  */
#define F11_2D_CTRL33_01          0x0075  /*  Large Z Scale Factor  */
#define F11_2D_CTRL34             0x0076  /*  Position Calculation & Post Correction  */
#define F11_2D_CTRL35             0x0077  /*  Z Pen Upper Threshold  */
#define F11_2D_CTRL36             0x0078  /*  Wx Scale Factor  */
#define F11_2D_CTRL37             0x0079  /*  Wx Offset  */
#define F11_2D_CTRL38             0x007A  /*  Wy Scale Factor  */
#define F11_2D_CTRL39             0x007B  /*  Wy Offset  */
#define F11_2D_CTRL40_00          0x007C  /*  X Pitch  */
#define F11_2D_CTRL40_01          0x007D  /*  X Pitch  */
#define F11_2D_CTRL41_00          0x007E  /*  Y Pitch  */
#define F11_2D_CTRL41_01          0x007F  /*  Y Pitch  */
#define F11_2D_CTRL42_00          0x0080  /*  Default Finger Width Tx  */
#define F11_2D_CTRL42_01          0x0081  /*  Default Finger Width Tx  */
#define F11_2D_CTRL43_00          0x0082  /*  Default Finger Width Ty  */
#define F11_2D_CTRL43_01          0x0083  /*  Default Finger Width Ty  */
#define F11_2D_CTRL44             0x0084  /*  Report Finger Width  */
#define F11_2D_CTRL45             0x0085  /*  Segmentation Aggressiveness  */
#define F11_2D_CTRL46             0x0086  /*  Rx Clip Low  */
#define F11_2D_CTRL47             0x0087  /*  Rx Clip High  */
#define F11_2D_CTRL48             0x0088  /*  Tx Clip Low  */
#define F11_2D_CTRL49             0x0089  /*  Tx Clip High  */
#define F11_2D_CTRL50             0x008A  /*  Minimum Finger Separation  */
#define F11_2D_CTRL51             0x008B  /*  Maximum Finger Movement  */
#define F11_2D_CTRL58             0x008C  /*  Large Object Suppression Parameters  */
#define F11_2D_CTRL68_00          0x008D  /*  Hover Rejection Curve Quadratic Coefficient LSB  */
#define F11_2D_CTRL68_01          0x008E  /*  Hover Rejection Curve Quadratic Coefficient MSB  */
#define F11_2D_CTRL68_02          0x008F  /*  Hover Rejection Curve Linear Coefficient LSB  */
#define F11_2D_CTRL68_03          0x0090  /*  Hover Rejection Curve Linear Coefficient MSB  */
#define F11_2D_CTRL68_04          0x0091  /*  Hover Rejection Curve Constant Term LSB  */
#define F11_2D_CTRL68_05          0x0092  /*  Hover Rejection Curve Constant Term MSB  */
#define F11_2D_CTRL69             0x0093  /*  Pen/Hover Hysteresis  */
#define F11_2D_CTRL70             0x0094  /*  Pen Temporal Filter  */
#define F11_2D_CTRL71             0x0095  /*  Pen Border Reporting Rejection Zone  */
#define F11_2D_CTRL72             0x0096  /*  Z Offset Tolerance of Hover Rejection  */
#define F11_2D_CTRL73             0x0097  /*  Jitter Control 1  */
#define F11_2D_CTRL74             0x0098  /*  Jitter Control 2  */
#define F11_2D_CTRL75_00          0x0099  /*  Jitter Control 3  */
#define F11_2D_CTRL75_01          0x009A  /*  Jitter Control 3  */
#define F11_2D_CTRL75_02          0x009B  /*  Jitter Control 3  */
#define F11_2D_CTRL76_00          0x009C  /*  Jitter Control 4  */
#define F11_2D_CTRL76_01          0x009D  /*  Jitter Control 4  */
#define F11_2D_CTRL76_02          0x009E  /*  Jitter Control 4  */
#define F11_2D_CTRL77             0x009F  /*  2D RX Number  */
#define F11_2D_CTRL78             0x00A0  /*  2D TX Number  */
#define F54_ANALOG_CTRL00         0x010B  /*  General Control  */
#define F54_ANALOG_CTRL01         0x010C  /*  General Control 1  */
#define F54_ANALOG_CTRL02_00      0x010D  /*  Saturation Capacitance Low  */
#define F54_ANALOG_CTRL02_01      0x010E  /*  Saturation Capacitance High  */
#define F54_ANALOG_CTRL03         0x010F  /*  Pixel Touch Threshold  */
#define F54_ANALOG_CTRL04         0x0110  /*  Misc Analog Control  */
#define F54_ANALOG_CTRL05         0x0111  /*  RefCap RefLo Settings  */
#define F54_ANALOG_CTRL06         0x0112  /*  RefCap RefHi Settings  */
#define F54_ANALOG_CTRL07         0x0113  /*  CBC Cap Settings  */
#define F54_ANALOG_CTRL08_00      0x0114  /*  Integration Duration Low  */
#define F54_ANALOG_CTRL08_01      0x0115  /*  Integration Duration High  */
#define F54_ANALOG_CTRL09         0x0116  /*  Reset Duration  */
#define F54_ANALOG_CTRL10         0x0117  /*  Noise Measurement Control  */
#define F54_ANALOG_CTRL11_00      0x0118  /*  Doze Wakeup Threshold Low  */
#define F54_ANALOG_CTRL11_01      0x0119  /*  Doze Wakeup Threshold High  */
#define F54_ANALOG_CTRL12         0x011A  /*  Slow Relaxation Rate  */
#define F54_ANALOG_CTRL13         0x011B  /*  Fast Relaxation Rate  */
#define F54_ANALOG_CTRL14         0x011C  /*  Sensor Physical Properties  */
#define F54_ANALOG_CTRL15_00      0x011D  /*  Sensor Rx Mapping 0  */
#define F54_ANALOG_CTRL15_01      0x011E  /*  Sensor Rx Mapping 1  */
#define F54_ANALOG_CTRL15_02      0x011F  /*  Sensor Rx Mapping 2  */
#define F54_ANALOG_CTRL15_03      0x0120  /*  Sensor Rx Mapping 3  */
#define F54_ANALOG_CTRL15_04      0x0121  /*  Sensor Rx Mapping 4  */
#define F54_ANALOG_CTRL15_05      0x0122  /*  Sensor Rx Mapping 5  */
#define F54_ANALOG_CTRL15_06      0x0123  /*  Sensor Rx Mapping 6  */
#define F54_ANALOG_CTRL15_07      0x0124  /*  Sensor Rx Mapping 7  */
#define F54_ANALOG_CTRL15_08      0x0125  /*  Sensor Rx Mapping 8  */
#define F54_ANALOG_CTRL15_09      0x0126  /*  Sensor Rx Mapping 9  */
#define F54_ANALOG_CTRL15_10      0x0127  /*  Sensor Rx Mapping 10  */
#define F54_ANALOG_CTRL15_11      0x0128  /*  Sensor Rx Mapping 11  */
#define F54_ANALOG_CTRL15_12      0x0129  /*  Sensor Rx Mapping 12  */
#define F54_ANALOG_CTRL15_13      0x012A  /*  Sensor Rx Mapping 13  */
#define F54_ANALOG_CTRL15_14      0x012B  /*  Sensor Rx Mapping 14  */
#define F54_ANALOG_CTRL15_15      0x012C  /*  Sensor Rx Mapping 15  */
#define F54_ANALOG_CTRL15_16      0x012D  /*  Sensor Rx Mapping 16  */
#define F54_ANALOG_CTRL15_17      0x012E  /*  Sensor Rx Mapping 17  */
#define F54_ANALOG_CTRL15_18      0x012F  /*  Sensor Rx Mapping 18  */
#define F54_ANALOG_CTRL16_00      0x0130  /*  Sensor Tx Mapping 0  */
#define F54_ANALOG_CTRL16_01      0x0131  /*  Sensor Tx Mapping 1  */
#define F54_ANALOG_CTRL16_02      0x0132  /*  Sensor Tx Mapping 2  */
#define F54_ANALOG_CTRL16_03      0x0133  /*  Sensor Tx Mapping 3  */
#define F54_ANALOG_CTRL16_04      0x0134  /*  Sensor Tx Mapping 4  */
#define F54_ANALOG_CTRL16_05      0x0135  /*  Sensor Tx Mapping 5  */
#define F54_ANALOG_CTRL16_06      0x0136  /*  Sensor Tx Mapping 6  */
#define F54_ANALOG_CTRL16_07      0x0137  /*  Sensor Tx Mapping 7  */
#define F54_ANALOG_CTRL16_08      0x0138  /*  Sensor Tx Mapping 8  */
#define F54_ANALOG_CTRL16_09      0x0139  /*  Sensor Tx Mapping 9  */
#define F54_ANALOG_CTRL16_10      0x013A  /*  Sensor Tx Mapping 10  */
#define F54_ANALOG_CTRL17_00      0x013B  /*  Sense Frequency Control0 0  */
#define F54_ANALOG_CTRL17_01      0x013C  /*  Sense Frequency Control0 1  */
#define F54_ANALOG_CTRL17_02      0x013D  /*  Sense Frequency Control0 2  */
#define F54_ANALOG_CTRL17_03      0x013E  /*  Sense Frequency Control0 3  */
#define F54_ANALOG_CTRL17_04      0x013F  /*  Sense Frequency Control0 4  */
#define F54_ANALOG_CTRL17_05      0x0140  /*  Sense Frequency Control0 5  */
#define F54_ANALOG_CTRL17_06      0x0141  /*  Sense Frequency Control0 6  */
#define F54_ANALOG_CTRL17_07      0x0142  /*  Sense Frequency Control0 7  */
#define F54_ANALOG_CTRL18_00      0x0143  /*  Sense Frequency Control Low 0  */
#define F54_ANALOG_CTRL18_01      0x0144  /*  Sense Frequency Control Low 1  */
#define F54_ANALOG_CTRL18_02      0x0145  /*  Sense Frequency Control Low 2  */
#define F54_ANALOG_CTRL18_03      0x0146  /*  Sense Frequency Control Low 3  */
#define F54_ANALOG_CTRL18_04      0x0147  /*  Sense Frequency Control Low 4  */
#define F54_ANALOG_CTRL18_05      0x0148  /*  Sense Frequency Control Low 5  */
#define F54_ANALOG_CTRL18_06      0x0149  /*  Sense Frequency Control Low 6  */
#define F54_ANALOG_CTRL18_07      0x014A  /*  Sense Frequency Control Low 7  */
#define F54_ANALOG_CTRL19_00      0x014B  /*  Sense Frequency Control2 0  */
#define F54_ANALOG_CTRL19_01      0x014C  /*  Sense Frequency Control2 1  */
#define F54_ANALOG_CTRL19_02      0x014D  /*  Sense Frequency Control2 2  */
#define F54_ANALOG_CTRL19_03      0x014E  /*  Sense Frequency Control2 3  */
#define F54_ANALOG_CTRL19_04      0x014F  /*  Sense Frequency Control2 4  */
#define F54_ANALOG_CTRL19_05      0x0150  /*  Sense Frequency Control2 5  */
#define F54_ANALOG_CTRL19_06      0x0151  /*  Sense Frequency Control2 6  */
#define F54_ANALOG_CTRL19_07      0x0152  /*  Sense Frequency Control2 7  */
#define F54_ANALOG_CTRL20         0x0153  /*  Noise Mitigation General Control  */
#define F54_ANALOG_CTRL21_00      0x0154  /*  HNM Frequency Shift Noise Threshold Low  */
#define F54_ANALOG_CTRL21_01      0x0155  /*  HNM Frequency Shift Noise Threshold High  */
#define F54_ANALOG_CTRL22         0x0156  /*  HNM Exit Density  */
#define F54_ANALOG_CTRL23_00      0x0157  /*  Medium Noise Threshold Low  */
#define F54_ANALOG_CTRL23_01      0x0158  /*  Medium Noise Threshold High  */
#define F54_ANALOG_CTRL24_00      0x0159  /*  High Noise Threshold Low  */
#define F54_ANALOG_CTRL24_01      0x015A  /*  High Noise Threshold High  */
#define F54_ANALOG_CTRL25         0x015B  /*  FNM Frequency Shift Density  */
#define F54_ANALOG_CTRL26         0x015C  /*  FNM Exit Threshold  */
#define F54_ANALOG_CTRL27         0x015D  /*  IIR Filter Coefficient  */
#define F54_ANALOG_CTRL28_00      0x015E  /*  FNM Frequency Shift Noise Threshold Low  */
#define F54_ANALOG_CTRL28_01      0x015F  /*  FNM Frequency Shift Noise Threshold High  */
#define F54_ANALOG_CTRL29         0x0160  /*  Common-Mode Noise Control  */
#define F54_ANALOG_CTRL30         0x0161  /*  CMN Cap Scale Factor  */
#define F54_ANALOG_CTRL31         0x0162  /*  Pixel Threshold Hysteresis  */
#define F54_ANALOG_CTRL32_00      0x0163  /*  Rx LowEdge Compensation Low  */
#define F54_ANALOG_CTRL32_01      0x0164  /*  Rx LowEdge Compensation High  */
#define F54_ANALOG_CTRL33_00      0x0165  /*  Rx HighEdge Compensation Low  */
#define F54_ANALOG_CTRL33_01      0x0166  /*  Rx HighEdge Compensation High  */
#define F54_ANALOG_CTRL34_00      0x0167  /*  Tx LowEdge Compensation Low  */
#define F54_ANALOG_CTRL34_01      0x0168  /*  Tx LowEdge Compensation High  */
#define F54_ANALOG_CTRL35_00      0x0169  /*  Tx HighEdge Compensation Low  */
#define F54_ANALOG_CTRL35_01      0x016A  /*  Tx HighEdge Compensation High  */
#define F54_ANALOG_CTRL36_00      0x016B  /*  Axis 1 Compensation 0  */
#define F54_ANALOG_CTRL36_01      0x016C  /*  Axis 1 Compensation 1  */
#define F54_ANALOG_CTRL36_02      0x016D  /*  Axis 1 Compensation 2  */
#define F54_ANALOG_CTRL36_03      0x016E  /*  Axis 1 Compensation 3  */
#define F54_ANALOG_CTRL36_04      0x016F  /*  Axis 1 Compensation 4  */
#define F54_ANALOG_CTRL36_05      0x0170  /*  Axis 1 Compensation 5  */
#define F54_ANALOG_CTRL36_06      0x0171  /*  Axis 1 Compensation 6  */
#define F54_ANALOG_CTRL36_07      0x0172  /*  Axis 1 Compensation 7  */
#define F54_ANALOG_CTRL36_08      0x0173  /*  Axis 1 Compensation 8  */
#define F54_ANALOG_CTRL36_09      0x0174  /*  Axis 1 Compensation 9  */
#define F54_ANALOG_CTRL36_10      0x0175  /*  Axis 1 Compensation 10  */
#define F54_ANALOG_CTRL36_11      0x0176  /*  Axis 1 Compensation 11  */
#define F54_ANALOG_CTRL36_12      0x0177  /*  Axis 1 Compensation 12  */
#define F54_ANALOG_CTRL36_13      0x0178  /*  Axis 1 Compensation 13  */
#define F54_ANALOG_CTRL36_14      0x0179  /*  Axis 1 Compensation 14  */
#define F54_ANALOG_CTRL36_15      0x017A  /*  Axis 1 Compensation 15  */
#define F54_ANALOG_CTRL36_16      0x017B  /*  Axis 1 Compensation 16  */
#define F54_ANALOG_CTRL36_17      0x017C  /*  Axis 1 Compensation 17  */
#define F54_ANALOG_CTRL36_18      0x017D  /*  Axis 1 Compensation 18  */
#define F54_ANALOG_CTRL38_00      0x017E  /*  Noise Control 1 0  */
#define F54_ANALOG_CTRL38_01      0x017F  /*  Noise Control 1 1  */
#define F54_ANALOG_CTRL38_02      0x0180  /*  Noise Control 1 2  */
#define F54_ANALOG_CTRL38_03      0x0181  /*  Noise Control 1 3  */
#define F54_ANALOG_CTRL38_04      0x0182  /*  Noise Control 1 4  */
#define F54_ANALOG_CTRL38_05      0x0183  /*  Noise Control 1 5  */
#define F54_ANALOG_CTRL38_06      0x0184  /*  Noise Control 1 6  */
#define F54_ANALOG_CTRL38_07      0x0185  /*  Noise Control 1 7  */
#define F54_ANALOG_CTRL39_00      0x0186  /*  Noise Control 2 0  */
#define F54_ANALOG_CTRL39_01      0x0187  /*  Noise Control 2 1  */
#define F54_ANALOG_CTRL39_02      0x0188  /*  Noise Control 2 2  */
#define F54_ANALOG_CTRL39_03      0x0189  /*  Noise Control 2 3  */
#define F54_ANALOG_CTRL39_04      0x018A  /*  Noise Control 2 4  */
#define F54_ANALOG_CTRL39_05      0x018B  /*  Noise Control 2 5  */
#define F54_ANALOG_CTRL39_06      0x018C  /*  Noise Control 2 6  */
#define F54_ANALOG_CTRL39_07      0x018D  /*  Noise Control 2 7  */
#define F54_ANALOG_CTRL40_00      0x018E  /*  Noise Control 3 0  */
#define F54_ANALOG_CTRL40_01      0x018F  /*  Noise Control 3 1  */
#define F54_ANALOG_CTRL40_02      0x0190  /*  Noise Control 3 2  */
#define F54_ANALOG_CTRL40_03      0x0191  /*  Noise Control 3 3  */
#define F54_ANALOG_CTRL40_04      0x0192  /*  Noise Control 3 4  */
#define F54_ANALOG_CTRL40_05      0x0193  /*  Noise Control 3 5  */
#define F54_ANALOG_CTRL40_06      0x0194  /*  Noise Control 3 6  */
#define F54_ANALOG_CTRL40_07      0x0195  /*  Noise Control 3 7  */
#define F54_ANALOG_CTRL41         0x0196  /*  Multi Metric Noise Mitigation Control  */
#define F54_ANALOG_CTRL42_00      0x0197  /*  Burst Span Metric Threshold Low  */
#define F54_ANALOG_CTRL42_01      0x0198  /*  Burst Span Metric Threshold High  */
#define F54_ANALOG_CTRL55         0x0199  /*  0D Slow Relaxation Rate  */
#define F54_ANALOG_CTRL56         0x019A  /*  0D Fast Relaxation Rate  */
#define F54_ANALOG_CTRL57         0x019B  /*  0D CBC Settings  */
#define F54_ANALOG_CTRL58         0x019C  /*  0D Acquisition Scheme  */
#define F1A_0D_CTRL00             0x0204  /*  General Control  */
#define F1A_0D_CTRL01_00          0x0205
#define F1A_0D_CTRL02_00          0x0206
#define F1A_0D_CTRL03_00          0x0207  /*  Tx Button 0  */
#define F1A_0D_CTRL03_01          0x0209  /*  Tx Button 1  */
#define F1A_0D_CTRL03_02          0x020B  /*  Tx Button 2  */
#define F1A_0D_CTRL03_03          0x020D  /*  Tx Button 3  */
#define F1A_0D_CTRL04_00          0x0208  /*  Rx Button 0  */
#define F1A_0D_CTRL04_01          0x020A  /*  Rx Button 1  */
#define F1A_0D_CTRL04_02          0x020C  /*  Rx Button 2  */
#define F1A_0D_CTRL04_03          0x020E  /*  Rx Button 3  */
#define F1A_0D_CTRL05_00          0x020F  /*  Touch Threshold Button 0  */
#define F1A_0D_CTRL05_01          0x0210  /*  Touch Threshold Button 1  */
#define F1A_0D_CTRL05_02          0x0211  /*  Touch Threshold Button 2  */
#define F1A_0D_CTRL05_03          0x0212  /*  Touch Threshold Button 3  */
#define F1A_0D_CTRL06             0x0213  /*  Release Threshold  */
#define F1A_0D_CTRL07             0x0214  /*  Strongest Button Hysteresis  */
#define F1A_0D_CTRL08             0x0215  /*  Filter Strength  */
#define F31_LED_CTRL00_00         0x0201  /*  LED Brightness 0  */
#define F31_LED_CTRL00_01         0x0202  /*  LED Brightness 1  */
#define F31_LED_CTRL00_02         0x0203  /*  LED Brightness 2  */


/**** Register values ****/
struct RegisterValue
{
    unsigned short Address;
    unsigned char Value;
};

struct RegisterValue value[] = {
  { F34_FLASH_CTRL00_00      , 0x51 },		/*  Customer Defined Config ID 0  */
  { F34_FLASH_CTRL00_01      , 0x4D },		/*  Customer Defined Config ID 1  */
  { F34_FLASH_CTRL00_02      , 0x41 },		/*  Customer Defined Config ID 2  */
  { F34_FLASH_CTRL00_03      , 0x4F },		/*  Customer Defined Config ID 3  */
  { F01_RMI_CTRL00           , 0x84 },		/*  Device Control  */
  { F01_RMI_CTRL01_00        , 0x3F },		/*  Interrupt Enable 0  */
  { F01_RMI_CTRL02           , 0x03 },		/*  Doze Period  */
  { F01_RMI_CTRL03           , 0x1E },		/*  Doze Wakeup Threshold  */
  { F01_RMI_CTRL05           , 0x05 },		/*  Extended Wait Before Doze  */
  { F01_RMI_CTRL06           , 0x70 },		/*  I2C Control  */
  { F01_RMI_CTRL08           , 0xC1 },		/*  Attention Control  */
  { F11_2D_CTRL00            , 0x08 },		/*  2D Report Mode  */
  { F11_2D_CTRL01            , 0x0B },		/*  2D Palm Detect  */
  { F11_2D_CTRL02            , 0x19 },		/*  2D Delta-X Thresh  */
  { F11_2D_CTRL03            , 0x19 },		/*  2D Delta-Y Thresh  */
  { F11_2D_CTRL04            , 0x00 },		/*  2D Velocity  */
  { F11_2D_CTRL05            , 0x00 },		/*  2D Acceleration  */
  { F11_2D_CTRL06            , 0x4C },		/*  2D Max X Position (7:0)  */
  { F11_2D_CTRL07            , 0x04 },		/*  2D Max X Position (11:8)  */
  { F11_2D_CTRL08            , 0x6C },		/*  2D Max Y Position (7:0)  */
  { F11_2D_CTRL09            , 0x07 },		/*  2D Max Y Position (11:8)  */
  { F11_2D_CTRL20            , 0x02 },		/*  2D Pen Enable  */
  { F11_2D_CTRL21            , 0x14 },		/*  Z Pen Lower Threshold  */
  { F11_2D_CTRL29            , 0x1E },		/*  Z Touch Threshold  */
  { F11_2D_CTRL30            , 0x05 },		/*  Z Touch Hysteresis  */
  { F11_2D_CTRL31            , 0x28 },		/*  Small Z Threshold  */
  { F11_2D_CTRL32_00         , 0xF5 },		/*  Small Z Scale Factor  */
  { F11_2D_CTRL32_01         , 0x28 },		/*  Small Z Scale Factor  */
  { F11_2D_CTRL33_00         , 0x1E },		/*  Large Z Scale Factor  */
  { F11_2D_CTRL33_01         , 0x05 },		/*  Large Z Scale Factor  */
  { F11_2D_CTRL34            , 0x01 },		/*  Position Calculation & Post Correction  */
  { F11_2D_CTRL35            , 0x3C },		/*  Z Pen Upper Threshold  */
  { F11_2D_CTRL36            , 0x30 },		/*  Wx Scale Factor  */
  { F11_2D_CTRL37            , 0x00 },		/*  Wx Offset  */
  { F11_2D_CTRL38            , 0x30 },		/*  Wy Scale Factor  */
  { F11_2D_CTRL39            , 0x00 },		/*  Wy Offset  */
  { F11_2D_CTRL40_00         , 0x00 },		/*  X Pitch  */
  { F11_2D_CTRL40_01         , 0x48 },		/*  X Pitch  */
  { F11_2D_CTRL41_00         , 0x00 },		/*  Y Pitch  */
  { F11_2D_CTRL41_01         , 0x48 },		/*  Y Pitch  */
  { F11_2D_CTRL42_00         , 0xF0 },		/*  Default Finger Width Tx  */
  { F11_2D_CTRL42_01         , 0xD2 },		/*  Default Finger Width Tx  */
  { F11_2D_CTRL43_00         , 0xF0 },		/*  Default Finger Width Ty  */
  { F11_2D_CTRL43_01         , 0xD2 },		/*  Default Finger Width Ty  */
  { F11_2D_CTRL44            , 0x00 },		/*  Report Finger Width  */
  { F11_2D_CTRL45            , 0x70 },		/*  Segmentation Aggressiveness  */
  { F11_2D_CTRL46            , 0x00 },		/*  Rx Clip Low  */
  { F11_2D_CTRL47            , 0x00 },		/*  Rx Clip High  */
  { F11_2D_CTRL48            , 0x00 },		/*  Tx Clip Low  */
  { F11_2D_CTRL49            , 0x00 },		/*  Tx Clip High  */
  { F11_2D_CTRL50            , 0x0A },		/*  Minimum Finger Separation  */
  { F11_2D_CTRL51            , 0x04 },		/*  Maximum Finger Movement  */
  { F11_2D_CTRL58            , 0xC0 },		/*  Large Object Suppression Parameters  */
  { F11_2D_CTRL68_00         , 0x00 },		/*  Hover Rejection Curve Quadratic Coefficient LSB  */
  { F11_2D_CTRL68_01         , 0x00 },		/*  Hover Rejection Curve Quadratic Coefficient MSB  */
  { F11_2D_CTRL68_02         , 0x00 },		/*  Hover Rejection Curve Linear Coefficient LSB  */
  { F11_2D_CTRL68_03         , 0x00 },		/*  Hover Rejection Curve Linear Coefficient MSB  */
  { F11_2D_CTRL68_04         , 0x00 },		/*  Hover Rejection Curve Constant Term LSB  */
  { F11_2D_CTRL68_05         , 0x00 },		/*  Hover Rejection Curve Constant Term MSB  */
  { F11_2D_CTRL69            , 0x19 },		/*  Pen/Hover Hysteresis  */
  { F11_2D_CTRL70            , 0x01 },		/*  Pen Temporal Filter  */
  { F11_2D_CTRL71            , 0x00 },		/*  Pen Border Reporting Rejection Zone  */
  { F11_2D_CTRL72            , 0x0A },		/*  Z Offset Tolerance of Hover Rejection  */
  { F11_2D_CTRL73            , 0x00 },		/*  Jitter Control 1  */
  { F11_2D_CTRL74            , 0x08 },		/*  Jitter Control 2  */
  { F11_2D_CTRL75_00         , 0xA2 },		/*  Jitter Control 3  */
  { F11_2D_CTRL75_01         , 0x02 },		/*  Jitter Control 3  */
  { F11_2D_CTRL75_02         , 0x32 },		/*  Jitter Control 3  */
  { F11_2D_CTRL76_00         , 0x0A },		/*  Jitter Control 4  */
  { F11_2D_CTRL76_01         , 0x0A },		/*  Jitter Control 4  */
  { F11_2D_CTRL76_02         , 0x96 },		/*  Jitter Control 4  */
  { F11_2D_CTRL77            , 0x13 },		/*  2D RX Number  */
  { F11_2D_CTRL78            , 0x0B },		/*  2D TX Number  */
  { F54_ANALOG_CTRL00        , 0x01 },		/*  General Control  */
  { F54_ANALOG_CTRL01        , 0x80 },		/*  General Control 1  */
  { F54_ANALOG_CTRL02_00     , 0x03 },		/*  Saturation Capacitance Low  */
  { F54_ANALOG_CTRL02_01     , 0x0E },		/*  Saturation Capacitance High  */
  { F54_ANALOG_CTRL03        , 0x1F },		/*  Pixel Touch Threshold  */
  { F54_ANALOG_CTRL04        , 0x00 },		/*  Misc Analog Control  */
  { F54_ANALOG_CTRL05        , 0xDB },		/*  RefCap RefLo Settings  */
  { F54_ANALOG_CTRL06        , 0x01 },		/*  RefCap RefHi Settings  */
  { F54_ANALOG_CTRL07        , 0x19 },		/*  CBC Cap Settings  */
  { F54_ANALOG_CTRL08_00     , 0x04 },		/*  Integration Duration Low  */
  { F54_ANALOG_CTRL08_01     , 0x1E },		/*  Integration Duration High  */
  { F54_ANALOG_CTRL09        , 0x00 },		/*  Reset Duration  */
  { F54_ANALOG_CTRL10        , 0x10 },		/*  Noise Measurement Control  */
  { F54_ANALOG_CTRL11_00     , 0x0A },		/*  Doze Wakeup Threshold Low  */
  { F54_ANALOG_CTRL11_01     , 0x00 },		/*  Doze Wakeup Threshold High  */
  { F54_ANALOG_CTRL12        , 0x01 },		/*  Slow Relaxation Rate  */
  { F54_ANALOG_CTRL13        , 0x03 },		/*  Fast Relaxation Rate  */
  { F54_ANALOG_CTRL14        , 0x12 },		/*  Sensor Physical Properties  */
  { F54_ANALOG_CTRL15_00     , 0x14 },		/*  Sensor Rx Mapping 0  */
  { F54_ANALOG_CTRL15_01     , 0x16 },		/*  Sensor Rx Mapping 1  */
  { F54_ANALOG_CTRL15_02     , 0x17 },		/*  Sensor Rx Mapping 2  */
  { F54_ANALOG_CTRL15_03     , 0x18 },		/*  Sensor Rx Mapping 3  */
  { F54_ANALOG_CTRL15_04     , 0x19 },		/*  Sensor Rx Mapping 4  */
  { F54_ANALOG_CTRL15_05     , 0x1B },		/*  Sensor Rx Mapping 5  */
  { F54_ANALOG_CTRL15_06     , 0x02 },		/*  Sensor Rx Mapping 6  */
  { F54_ANALOG_CTRL15_07     , 0x04 },		/*  Sensor Rx Mapping 7  */
  { F54_ANALOG_CTRL15_08     , 0x06 },		/*  Sensor Rx Mapping 8  */
  { F54_ANALOG_CTRL15_09     , 0x08 },		/*  Sensor Rx Mapping 9  */
  { F54_ANALOG_CTRL15_10     , 0x09 },		/*  Sensor Rx Mapping 10  */
  { F54_ANALOG_CTRL15_11     , 0x0B },		/*  Sensor Rx Mapping 11  */
  { F54_ANALOG_CTRL15_12     , 0x0D },		/*  Sensor Rx Mapping 12  */
  { F54_ANALOG_CTRL15_13     , 0x0F },		/*  Sensor Rx Mapping 13  */
  { F54_ANALOG_CTRL15_14     , 0x11 },		/*  Sensor Rx Mapping 14  */
  { F54_ANALOG_CTRL15_15     , 0x00 },		/*  Sensor Rx Mapping 15  */
  { F54_ANALOG_CTRL15_16     , 0x04 },		/*  Sensor Rx Mapping 16  */
  { F54_ANALOG_CTRL15_17     , 0x02 },		/*  Sensor Rx Mapping 17  */
  { F54_ANALOG_CTRL15_18     , 0x01 },		/*  Sensor Rx Mapping 18  */
  { F54_ANALOG_CTRL16_00     , 0x06 },		/*  Sensor Tx Mapping 0  */
  { F54_ANALOG_CTRL16_01     , 0x08 },		/*  Sensor Tx Mapping 1  */
  { F54_ANALOG_CTRL16_02     , 0x0A },		/*  Sensor Tx Mapping 2  */
  { F54_ANALOG_CTRL16_03     , 0x0C },		/*  Sensor Tx Mapping 3  */
  { F54_ANALOG_CTRL16_04     , 0x0E },		/*  Sensor Tx Mapping 4  */
  { F54_ANALOG_CTRL16_05     , 0x10 },		/*  Sensor Tx Mapping 5  */
  { F54_ANALOG_CTRL16_06     , 0x12 },		/*  Sensor Tx Mapping 6  */
  { F54_ANALOG_CTRL16_07     , 0x13 },		/*  Sensor Tx Mapping 7  */
  { F54_ANALOG_CTRL16_08     , 0xC0 },		/*  Sensor Tx Mapping 8  */
  { F54_ANALOG_CTRL16_09     , 0x00 },		/*  Sensor Tx Mapping 9  */
  { F54_ANALOG_CTRL16_10     , 0x00 },		/*  Sensor Tx Mapping 10  */
  { F54_ANALOG_CTRL17_00     , 0x00 },		/*  Sense Frequency Control0 0  */
  { F54_ANALOG_CTRL17_01     , 0x00 },		/*  Sense Frequency Control0 1  */
  { F54_ANALOG_CTRL17_02     , 0x00 },		/*  Sense Frequency Control0 2  */
  { F54_ANALOG_CTRL17_03     , 0x00 },		/*  Sense Frequency Control0 3  */
  { F54_ANALOG_CTRL17_04     , 0x00 },		/*  Sense Frequency Control0 4  */
  { F54_ANALOG_CTRL17_05     , 0x47 },		/*  Sense Frequency Control0 5  */
  { F54_ANALOG_CTRL17_06     , 0x00 },		/*  Sense Frequency Control0 6  */
  { F54_ANALOG_CTRL17_07     , 0x00 },		/*  Sense Frequency Control0 7  */
  { F54_ANALOG_CTRL18_00     , 0x00 },		/*  Sense Frequency Control Low 0  */
  { F54_ANALOG_CTRL18_01     , 0x00 },		/*  Sense Frequency Control Low 1  */
  { F54_ANALOG_CTRL18_02     , 0x00 },		/*  Sense Frequency Control Low 2  */
  { F54_ANALOG_CTRL18_03     , 0x00 },		/*  Sense Frequency Control Low 3  */
  { F54_ANALOG_CTRL18_04     , 0x00 },		/*  Sense Frequency Control Low 4  */
  { F54_ANALOG_CTRL18_05     , 0x00 },		/*  Sense Frequency Control Low 5  */
  { F54_ANALOG_CTRL18_06     , 0x00 },		/*  Sense Frequency Control Low 6  */
  { F54_ANALOG_CTRL18_07     , 0x00 },		/*  Sense Frequency Control Low 7  */
  { F54_ANALOG_CTRL19_00     , 0x00 },		/*  Sense Frequency Control2 0  */
  { F54_ANALOG_CTRL19_01     , 0x00 },		/*  Sense Frequency Control2 1  */
  { F54_ANALOG_CTRL19_02     , 0x00 },		/*  Sense Frequency Control2 2  */
  { F54_ANALOG_CTRL19_03     , 0x00 },		/*  Sense Frequency Control2 3  */
  { F54_ANALOG_CTRL19_04     , 0x00 },		/*  Sense Frequency Control2 4  */
  { F54_ANALOG_CTRL19_05     , 0x00 },		/*  Sense Frequency Control2 5  */
  { F54_ANALOG_CTRL19_06     , 0xBC },		/*  Sense Frequency Control2 6  */
  { F54_ANALOG_CTRL19_07     , 0x02 },		/*  Sense Frequency Control2 7  */
  { F54_ANALOG_CTRL20        , 0xFF },		/*  Noise Mitigation General Control  */
  { F54_ANALOG_CTRL21_00     , 0xFF },		/*  HNM Frequency Shift Noise Threshold Low  */
  { F54_ANALOG_CTRL21_01     , 0xFF },		/*  HNM Frequency Shift Noise Threshold High  */
  { F54_ANALOG_CTRL22        , 0xFF },		/*  HNM Exit Density  */
  { F54_ANALOG_CTRL23_00     , 0xFF },		/*  Medium Noise Threshold Low  */
  { F54_ANALOG_CTRL23_01     , 0xFF },		/*  Medium Noise Threshold High  */
  { F54_ANALOG_CTRL24_00     , 0xFF },		/*  High Noise Threshold Low  */
  { F54_ANALOG_CTRL24_01     , 0x00 },		/*  High Noise Threshold High  */
  { F54_ANALOG_CTRL25        , 0xFF },		/*  FNM Frequency Shift Density  */
  { F54_ANALOG_CTRL26        , 0xFF },		/*  FNM Exit Threshold  */
  { F54_ANALOG_CTRL27        , 0x00 },		/*  IIR Filter Coefficient  */
  { F54_ANALOG_CTRL28_00     , 0xC0 },		/*  FNM Frequency Shift Noise Threshold Low  */
  { F54_ANALOG_CTRL28_01     , 0x80 },		/*  FNM Frequency Shift Noise Threshold High  */
  { F54_ANALOG_CTRL29        , 0x00 },		/*  Common-Mode Noise Control  */
  { F54_ANALOG_CTRL30        , 0x10 },		/*  CMN Cap Scale Factor  */
  { F54_ANALOG_CTRL31        , 0x00 },		/*  Pixel Threshold Hysteresis  */
  { F54_ANALOG_CTRL32_00     , 0x10 },		/*  Rx LowEdge Compensation Low  */
  { F54_ANALOG_CTRL32_01     , 0x00 },		/*  Rx LowEdge Compensation High  */
  { F54_ANALOG_CTRL33_00     , 0x10 },		/*  Rx HighEdge Compensation Low  */
  { F54_ANALOG_CTRL33_01     , 0x00 },		/*  Rx HighEdge Compensation High  */
  { F54_ANALOG_CTRL34_00     , 0x10 },		/*  Tx LowEdge Compensation Low  */
  { F54_ANALOG_CTRL34_01     , 0x80 },		/*  Tx LowEdge Compensation High  */
  { F54_ANALOG_CTRL35_00     , 0x80 },		/*  Tx HighEdge Compensation Low  */
  { F54_ANALOG_CTRL35_01     , 0x80 },		/*  Tx HighEdge Compensation High  */
  { F54_ANALOG_CTRL36_00     , 0x80 },		/*  Axis 1 Compensation 0  */
  { F54_ANALOG_CTRL36_01     , 0x80 },		/*  Axis 1 Compensation 1  */
  { F54_ANALOG_CTRL36_02     , 0x80 },		/*  Axis 1 Compensation 2  */
  { F54_ANALOG_CTRL36_03     , 0x80 },		/*  Axis 1 Compensation 3  */
  { F54_ANALOG_CTRL36_04     , 0x80 },		/*  Axis 1 Compensation 4  */
  { F54_ANALOG_CTRL36_05     , 0x80 },		/*  Axis 1 Compensation 5  */
  { F54_ANALOG_CTRL36_06     , 0x80 },		/*  Axis 1 Compensation 6  */
  { F54_ANALOG_CTRL36_07     , 0x80 },		/*  Axis 1 Compensation 7  */
  { F54_ANALOG_CTRL36_08     , 0x80 },		/*  Axis 1 Compensation 8  */
  { F54_ANALOG_CTRL36_09     , 0x80 },		/*  Axis 1 Compensation 9  */
  { F54_ANALOG_CTRL36_10     , 0x80 },		/*  Axis 1 Compensation 10  */
  { F54_ANALOG_CTRL36_11     , 0x80 },		/*  Axis 1 Compensation 11  */
  { F54_ANALOG_CTRL36_12     , 0x80 },		/*  Axis 1 Compensation 12  */
  { F54_ANALOG_CTRL36_13     , 0x80 },		/*  Axis 1 Compensation 13  */
  { F54_ANALOG_CTRL36_14     , 0x80 },		/*  Axis 1 Compensation 14  */
  { F54_ANALOG_CTRL36_15     , 0x80 },		/*  Axis 1 Compensation 15  */
  { F54_ANALOG_CTRL36_16     , 0x08 },		/*  Axis 1 Compensation 16  */
  { F54_ANALOG_CTRL36_17     , 0x00 },		/*  Axis 1 Compensation 17  */
  { F54_ANALOG_CTRL36_18     , 0x00 },		/*  Axis 1 Compensation 18  */
  { F54_ANALOG_CTRL38_00     , 0x00 },		/*  Noise Control 1 0  */
  { F54_ANALOG_CTRL38_01     , 0x00 },		/*  Noise Control 1 1  */
  { F54_ANALOG_CTRL38_02     , 0x00 },		/*  Noise Control 1 2  */
  { F54_ANALOG_CTRL38_03     , 0x00 },		/*  Noise Control 1 3  */
  { F54_ANALOG_CTRL38_04     , 0x00 },		/*  Noise Control 1 4  */
  { F54_ANALOG_CTRL38_05     , 0x10 },		/*  Noise Control 1 5  */
  { F54_ANALOG_CTRL38_06     , 0x00 },		/*  Noise Control 1 6  */
  { F54_ANALOG_CTRL38_07     , 0x00 },		/*  Noise Control 1 7  */
  { F54_ANALOG_CTRL39_00     , 0x00 },		/*  Noise Control 2 0  */
  { F54_ANALOG_CTRL39_01     , 0x00 },		/*  Noise Control 2 1  */
  { F54_ANALOG_CTRL39_02     , 0x00 },		/*  Noise Control 2 2  */
  { F54_ANALOG_CTRL39_03     , 0x00 },		/*  Noise Control 2 3  */
  { F54_ANALOG_CTRL39_04     , 0x00 },		/*  Noise Control 2 4  */
  { F54_ANALOG_CTRL39_05     , 0x00 },		/*  Noise Control 2 5  */
  { F54_ANALOG_CTRL39_06     , 0x00 },		/*  Noise Control 2 6  */
  { F54_ANALOG_CTRL39_07     , 0x00 },		/*  Noise Control 2 7  */
  { F54_ANALOG_CTRL40_00     , 0x00 },		/*  Noise Control 3 0  */
  { F54_ANALOG_CTRL40_01     , 0x00 },		/*  Noise Control 3 1  */
  { F54_ANALOG_CTRL40_02     , 0x00 },		/*  Noise Control 3 2  */
  { F54_ANALOG_CTRL40_03     , 0x00 },		/*  Noise Control 3 3  */
  { F54_ANALOG_CTRL40_04     , 0x00 },		/*  Noise Control 3 4  */
  { F54_ANALOG_CTRL40_05     , 0x00 },		/*  Noise Control 3 5  */
  { F54_ANALOG_CTRL40_06     , 0x30 },		/*  Noise Control 3 6  */
  { F54_ANALOG_CTRL40_07     , 0x30 },		/*  Noise Control 3 7  */
  { F54_ANALOG_CTRL41        , 0x10 },		/*  Multi Metric Noise Mitigation Control  */
  { F54_ANALOG_CTRL42_00     , 0x0A },		/*  Burst Span Metric Threshold Low  */
  { F54_ANALOG_CTRL42_01     , 0x0A },		/*  Burst Span Metric Threshold High  */
  { F54_ANALOG_CTRL55        , 0x00 },		/*  0D Slow Relaxation Rate  */
  { F54_ANALOG_CTRL56        , 0x00 },		/*  0D Fast Relaxation Rate  */
  { F54_ANALOG_CTRL57        , 0x00 },		/*  0D CBC Settings  */
  { F54_ANALOG_CTRL58        , 0x00 },		/*  0D Acquisition Scheme  */
  { F1A_0D_CTRL00            , 0x00 },		/*  General Control  */
  { F1A_0D_CTRL01_00         , 0x0F },
  { F1A_0D_CTRL02_00         , 0x0F },
  { F1A_0D_CTRL03_00         , 0xFF },		/*  Tx Button 0  */
  { F1A_0D_CTRL03_01         , 0xFF },		/*  Tx Button 1  */
  { F1A_0D_CTRL03_02         , 0xFF },		/*  Tx Button 2  */
  { F1A_0D_CTRL03_03         , 0xFF },		/*  Tx Button 3  */
  { F1A_0D_CTRL04_00         , 0xFF },		/*  Rx Button 0  */
  { F1A_0D_CTRL04_01         , 0xFF },		/*  Rx Button 1  */
  { F1A_0D_CTRL04_02         , 0xFF },		/*  Rx Button 2  */
  { F1A_0D_CTRL04_03         , 0xFF },		/*  Rx Button 3  */
  { F1A_0D_CTRL05_00         , 0x51 },		/*  Touch Threshold Button 0  */
  { F1A_0D_CTRL05_01         , 0x51 },		/*  Touch Threshold Button 1  */
  { F1A_0D_CTRL05_02         , 0x51 },		/*  Touch Threshold Button 2  */
  { F1A_0D_CTRL05_03         , 0x51 },		/*  Touch Threshold Button 3  */
  { F1A_0D_CTRL06            , 0x66 },		/*  Release Threshold  */
  { F1A_0D_CTRL07            , 0x1A },		/*  Strongest Button Hysteresis  */
  { F1A_0D_CTRL08            , 0x04 },		/*  Filter Strength  */
  { F31_LED_CTRL00_00        , 0x00 },		/*  LED Brightness 0  */
  { F31_LED_CTRL00_01        , 0x02 },		/*  LED Brightness 1  */
  { F31_LED_CTRL00_02        , 0xF4 } 		/*  LED Brightness 2  */
};


/**** Protocol info ****/
#define AE_LOW 0
#define AE_HIGH 1
#define ATTENTION AE_LOW
#define PROTOCOL_I2C 1
#define PROTOCOL_I2C_SLAVE_ADDR 0x70
