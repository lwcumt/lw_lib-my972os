#include"pinyin.h"


//"ƴ�����뷨�������б�"
const unsigned char PY_mb_space []={""};
const unsigned char PY_mb_a     []={"����߹�����"};
const unsigned char PY_mb_ai    []={"�������������������������������������������"};
const unsigned char PY_mb_an    []={"�����������������������������������"};
const unsigned char PY_mb_ang   []={"������"};
const unsigned char PY_mb_ao    []={"�������������°ð���������������������������"};
const unsigned char PY_mb_ba    []={"�ŰưǰȰɰʰ˰̰ͰΰϰаѰҰӰ԰հ���������������"};
const unsigned char PY_mb_bai   []={"�װذٰڰ۰ܰݰ޲�����"};
const unsigned char PY_mb_ban   []={"�߰��������������������������"};
const unsigned char PY_mb_bang  []={"���������������������"};
const unsigned char PY_mb_bao   []={"�����������������������������������������������������"};
const unsigned char PY_mb_bei   []={"���������������������������������������������������������"};
const unsigned char PY_mb_ben   []={"���������������"};
const unsigned char PY_mb_beng  []={"�������±ñı�ܡ���"};
const unsigned char PY_mb_bi    []={"�ƱǱȱɱʱ˱̱ͱαϱбѱұӱԱձֱױرٱڱ۱ܱ�����ذ��������ݩ��޵�������������������������������������������"};
const unsigned char PY_mb_bian  []={"�ޱ߱������������������������������������"};
const unsigned char PY_mb_biao  []={"�������������������������"};
const unsigned char PY_mb_bie   []={"�������"};
const unsigned char PY_mb_bin   []={"������������������������������"};
const unsigned char PY_mb_bing  []={"������������������������������"};
const unsigned char PY_mb_bo    []={"�ذٰ�����������������������������������������������ެ�������������������"};
const unsigned char PY_mb_bu    []={"��������������������������߲�����������"};
const unsigned char PY_mb_ca    []={"������"};
const unsigned char PY_mb_cai   []={"�²òĲŲƲǲȲɲʲ˲�"};
const unsigned char PY_mb_can   []={"�ͲβϲвѲҲ����������"};
const unsigned char PY_mb_cang  []={"�Բղֲײ���"};
const unsigned char PY_mb_cao   []={"�ٲڲ۲ܲ�ܳ�������"};
const unsigned char PY_mb_ce    []={"�޲߲�����"};
const unsigned char PY_mb_cen   []={"����"}; 
const unsigned char PY_mb_ceng  []={"�������"};
const unsigned char PY_mb_cha   []={"������������ɲ���������������������"};
const unsigned char PY_mb_chai  []={"�����٭�������"};
const unsigned char PY_mb_chan  []={"������������������������������������������������"};
const unsigned char PY_mb_chang []={"�������������������������������������������������"};
const unsigned char PY_mb_chao  []={"�������������������½�������"};
const unsigned char PY_mb_che   []={"�����������������"};
const unsigned char PY_mb_chen  []={"���������������³óĳ����������������"};
const unsigned char PY_mb_cheng []={"�ųƳǳȳɳʳ˳̳ͳγϳгѳҳ�ʢة�����������������������"};
const unsigned char PY_mb_chi   []={"�Գճֳ׳سٳڳ۳ܳݳ޳߳��������ܯ��߳������������������������������"};
const unsigned char PY_mb_chong []={"��������������������"};
const unsigned char PY_mb_chou  []={"�������������ٱ������"};
const unsigned char PY_mb_chu   []={"����������������������������������ءۻ�������������������"};
const unsigned char PY_mb_chuai []={"����������"};
const unsigned char PY_mb_chuan []={"������������������������"};
const unsigned char PY_mb_chuang[]={"����������������"};
const unsigned char PY_mb_chui  []={"��������������"};
const unsigned char PY_mb_chun  []={"��������������ݻ����"};
const unsigned char PY_mb_chuo  []={"������������"};
const unsigned char PY_mb_ci    []={"��ôĴŴƴǴȴɴʴ˴̴ʹ�����������������"};
const unsigned char PY_mb_cong  []={"�ϴдѴҴӴ������������"};
const unsigned char PY_mb_cou   []={"������"};
const unsigned char PY_mb_cu    []={"�ִ״ش��������������"};
const unsigned char PY_mb_cuan  []={"�ڴ۴�����ߥ����"};
const unsigned char PY_mb_cui   []={"�ݴ޴ߴ����������������"};
const unsigned char PY_mb_cun   []={"��������"};
const unsigned char PY_mb_cuo   []={"��������������������������"};
const unsigned char PY_mb_da    []={"��������������������������"};
const unsigned char PY_mb_dai   []={"�������������������������ܤ߰߾����������"};
const unsigned char PY_mb_dan   []={"��������������������������������ʯ��������������������"};
const unsigned char PY_mb_dang  []={"����������������������"};
const unsigned char PY_mb_dao   []={"��������������������������߶���������"};
const unsigned char PY_mb_de    []={"�µõĵ��"};
const unsigned char PY_mb_dei   []={"��"};
const unsigned char PY_mb_deng  []={"�εŵƵǵȵɵʵ������������"};
const unsigned char PY_mb_di    []={"�ĵ̵͵εϵеѵҵӵԵյֵ׵صٵڵ۵ܵݵ���ص��ڮ��ۡ��ݶ��������������������"};
const unsigned char PY_mb_dia   []={"��"};
const unsigned char PY_mb_dian  []={"�ߵ�������������������������������"};
const unsigned char PY_mb_diao  []={"��������������������"};
const unsigned char PY_mb_die   []={"����������������ܦ�����������"};
const unsigned char PY_mb_ding  []={"������������������������������������"};
const unsigned char PY_mb_diu   []={"����"};
const unsigned char PY_mb_dong  []={"��������������������������������"};
const unsigned char PY_mb_dou   []={"����������������������"};
const unsigned char PY_mb_du    []={"�������������¶öĶŶƶǶȶɶ�ܶ�������������"};
const unsigned char PY_mb_duan  []={"�˶̶Ͷζ϶������"};
const unsigned char PY_mb_dui   []={"�ѶҶӶ�����"};
const unsigned char PY_mb_dun   []={"�նֶ׶ضٶڶ۶ܶ��������������"};
const unsigned char PY_mb_duo   []={"�ȶ޶߶�������������������������"};
const unsigned char PY_mb_e     []={"������������������Ŷج������ݭ��������������������"};
const unsigned char PY_mb_ei    []={"��"};
const unsigned char PY_mb_en    []={"��������"};
const unsigned char PY_mb_er    []={"�������������������������"};
const unsigned char PY_mb_fa    []={"��������������������"};
const unsigned char PY_mb_fan   []={"����������������������������������ެ����������"};
const unsigned char PY_mb_fang  []={"���������������·÷ķ�������������"};
const unsigned char PY_mb_fei   []={"�ƷǷȷɷʷ˷̷ͷηϷз�����������������������������������"};
const unsigned char PY_mb_fen   []={"�ҷӷԷշַ׷طٷڷ۷ܷݷ޷߷��������������"};
const unsigned char PY_mb_feng  []={"����������������ٺۺ�������"};
const unsigned char PY_mb_fo    []={"��"};
const unsigned char PY_mb_fou   []={"���"};
const unsigned char PY_mb_fu    []={"�����������������������������������������������������������������������������������������������ۮܽ������ݳ����߻����������������������������������������������"};
const unsigned char PY_mb_ga    []={"���¼п�٤���������"};
const unsigned char PY_mb_gai   []={"�øĸŸƸǸȽ�ؤ���������"};
const unsigned char PY_mb_gan   []={"�ɸʸ˸̸͸θϸиѸҸ�������ߦ���������������"};
const unsigned char PY_mb_gang  []={"�Ըոָ׸ظٸڸ۸ܿ�����"};
const unsigned char PY_mb_gao   []={"�ݸ޸߸�������غھ۬޻��������"};
const unsigned char PY_mb_ge    []={"�Ǹ���������������������Ͽ�ت������ܪ������������������"};
const unsigned char PY_mb_gei   []={"��"};
const unsigned char PY_mb_gen   []={"����بݢ����"};
const unsigned char PY_mb_geng  []={"�����������������������"};
const unsigned char PY_mb_gong  []={"���������������������������������������"};
const unsigned char PY_mb_gou   []={"��������������������ڸ������������������"};
const unsigned char PY_mb_gu    []={"�������������¹ùĹŹƹǹȹɹʹ˹̹ͼ���ڬ��������������������������������������"};
const unsigned char PY_mb_gua   []={"�ιϹйѹҹ���ڴ�������"};
const unsigned char PY_mb_guai  []={"�Թչ���"};
const unsigned char PY_mb_guan  []={"�׹عٹڹ۹ܹݹ޹߹������ݸ����������"};
const unsigned char PY_mb_guang []={"������������"};
const unsigned char PY_mb_gui   []={"�����������������Ȳ���������������������"};
const unsigned char PY_mb_gun   []={"�������������"};
const unsigned char PY_mb_guo   []={"������������������������������������"};
const unsigned char PY_mb_ha    []={"�����"};
const unsigned char PY_mb_hai   []={"������������������������"};
const unsigned char PY_mb_han   []={"��������������������������������������������������������"};
const unsigned char PY_mb_hang  []={"�����������������"};
const unsigned char PY_mb_hao   []={"�亾�������ºúĺźƺ���޶����������"};
const unsigned char PY_mb_he    []={"�ǺȺɺʺ˺̺ͺκϺкѺҺӺԺպֺ׺���ڭ�������������������"};
const unsigned char PY_mb_hei   []={"�ٺ�"};
const unsigned char PY_mb_hen   []={"�ۺܺݺ�"};
const unsigned char PY_mb_heng  []={"�ߺ����޿����"};
const unsigned char PY_mb_hong  []={"��������������ڧݦޮް����"};
const unsigned char PY_mb_hou   []={"��������ܩ��������������"};
const unsigned char PY_mb_hu    []={"�˺����������������������������������������������������������������������������������"};
const unsigned char PY_mb_hua   []={"�������������������������"};
const unsigned char PY_mb_huai  []={"������������"};
const unsigned char PY_mb_huan  []={"�������������������������»�ۨۼ����ߧ������������������"};
const unsigned char PY_mb_huang []={"�ĻŻƻǻȻɻʻ˻̻ͻλϻл��������������������"};
const unsigned char PY_mb_hui   []={"�һӻԻջֻ׻ػٻڻۻܻݻ޻߻���������ڶ����ޥ����������������������"};
const unsigned char PY_mb_hun   []={"�������ڻ��������"};
const unsigned char PY_mb_huo   []={"�ͻ��������������޽߫������������"};
const unsigned char PY_mb_ji    []={"�������������������������������������������������������������������������������������¼üļżƼǼȼɼʼ˼̼ͽ���ϵآؽ����٥����ܸ����ݽ��ު��ߴ�����������������������������������������������������������"};
const unsigned char PY_mb_jia   []={"�μϼмѼҼӼԼռּ׼ؼټڼۼܼݼ�����٤ۣ��������������������������������"};
const unsigned char PY_mb_jian  []={"�߼���������������������������������������������������������������������������������������������������������������"};
const unsigned char PY_mb_jiang []={"�罩������������������������ǿ����������������"};
const unsigned char PY_mb_jiao  []={"�������������������������½ýĽŽƽǽȽɽʽ˽̽ͽνϽнѾ�Уٮ��ܴ����������������������"};
const unsigned char PY_mb_jie   []={"�ҽӽԽսֽ׽ؽٽڽ۽ܽݽ޽߽���������������ڦڵ�������������������������"};
const unsigned char PY_mb_jin   []={"�����������������������������������ݣ������������������������"};
const unsigned char PY_mb_jing  []={"������������������������������������������������������������ݼ������������������"};
const unsigned char PY_mb_jiong []={"����������"};
const unsigned char PY_mb_jiu   []={"���������¾þľžƾǾȾɾʾ˾̾;�����������������"};
const unsigned char PY_mb_ju    []={"����ϾоѾҾӾԾվ־׾ؾپھ۾ܾݾ޾߾����������ڪ��������������������������������������������"};
const unsigned char PY_mb_juan  []={"��������Ȧ۲�������������"};
const unsigned char PY_mb_jue   []={"���ŽǾ����������������������ܥާ���������������������"};
const unsigned char PY_mb_jun   []={"�������������������������������"};
const unsigned char PY_mb_ka    []={"��������������"};
const unsigned char PY_mb_kai   []={"�������������������������"};
const unsigned char PY_mb_kan   []={"��������������٩��ݨ������"};
const unsigned char PY_mb_kang  []={"��������������������"};
const unsigned char PY_mb_kao   []={"����������������"};
const unsigned char PY_mb_ke    []={"�ǿ����¿ÿĿſƿǿȿɿʿ˿̿Ϳ��������������������������������"};
const unsigned char PY_mb_ken   []={"�Ͽпѿ���"};
const unsigned char PY_mb_keng  []={"�ӿ������"};
const unsigned char PY_mb_kong  []={"�տֿ׿�������"};
const unsigned char PY_mb_kou   []={"�ٿڿۿ���ޢߵ����"};
const unsigned char PY_mb_ku    []={"�ݿ޿߿������ܥ����"};
const unsigned char PY_mb_kua   []={"������٨�"};
const unsigned char PY_mb_kuai  []={"��������ۦ������"};
const unsigned char PY_mb_kuan  []={"�����"};
const unsigned char PY_mb_kuang []={"�����������ڲڿ������������"};
const unsigned char PY_mb_kui   []={"����������������������ظ���������������������������"};
const unsigned char PY_mb_kun   []={"��������������������"};
const unsigned char PY_mb_kuo   []={"����������"};
const unsigned char PY_mb_la    []={"�������������������������"};
const unsigned char PY_mb_lai   []={"���������������������"};
const unsigned char PY_mb_lan   []={"����������������������������������������"};
const unsigned char PY_mb_lang  []={"��������������ݹ����������"};
const unsigned char PY_mb_lao   []={"�������������������������������������"};
const unsigned char PY_mb_le    []={"��������߷����"};
const unsigned char PY_mb_lei   []={"��������������������������ڳ������������"};
const unsigned char PY_mb_leng  []={"������ܨ�"};
const unsigned char PY_mb_li    []={"��������������������������������������������������������������������تٳٵ۪����ݰ��޼߿�����������������������������������������������������������"};
const unsigned char PY_mb_lia   []={"��"};
const unsigned char PY_mb_lian  []={"������������������������������������������������"};
const unsigned char PY_mb_liang []={"������������������������ܮݹ�����"};
const unsigned char PY_mb_liao  []={"��������������������������ޤ������������"};
const unsigned char PY_mb_lie   []={"�������������������������"};
const unsigned char PY_mb_lin   []={"�����������������������������������������������"};
const unsigned char PY_mb_ling  []={"������������������������������۹����������������������"};
const unsigned char PY_mb_liu   []={"����������������������µ½����������������"};
const unsigned char PY_mb_lo    []={"��"};
const unsigned char PY_mb_long  []={"����������¡¢£¤Ū���������������"};
const unsigned char PY_mb_lou   []={"¥¦§¨©ª¶�����������������"};
const unsigned char PY_mb_lu    []={"��«¬­®¯°±²³´µ¶·¸¹º»¼½¾����ߣ������������������������������������"};
const unsigned char PY_mb_luan  []={"��������������������"};
const unsigned char PY_mb_lve   []={"�����"};
const unsigned char PY_mb_lun   []={"����������������"};
const unsigned char PY_mb_luo   []={"���������������������������������������������������������"};
const unsigned char PY_mb_lv    []={"¿���������������������������������������"};
const unsigned char PY_mb_m     []={"߼"}; 
const unsigned char PY_mb_ma    []={"������������������ĦĨ��������"};
const unsigned char PY_mb_mai   []={"������������۽ݤ��"};
const unsigned char PY_mb_man   []={"������������������áܬ��������������"};
const unsigned char PY_mb_mang  []={"âãäåæç��������"};
const unsigned char PY_mb_mao   []={"èéêëìíîïðñòó���������������������"};
const unsigned char PY_mb_me    []={"ô"};
const unsigned char PY_mb_mei   []={"õö÷øùúûüýþÿ����������ݮ���������������"};
const unsigned char PY_mb_men   []={"�������������"};
const unsigned char PY_mb_meng  []={"��������������������ޫ��������������"};
const unsigned char PY_mb_mi    []={"������������������������������ڢ����������������������������"};
const unsigned char PY_mb_mian  []={"�����������������������������"};
const unsigned char PY_mb_miao  []={"������������������������������"};
const unsigned char PY_mb_mie   []={"����ؿ�����"};
const unsigned char PY_mb_min   []={"������������������������������"};
const unsigned char PY_mb_ming  []={"������������ڤ���������"};
const unsigned char PY_mb_miu   []={"����"};
const unsigned char PY_mb_mo    []={"��û��ġĢģĤĥĦħĨĩĪīĬĭĮįİ���������������������������"};
const unsigned char PY_mb_mou   []={"ıĲĳٰ����������"};
const unsigned char PY_mb_mu    []={"ģĲĴĵĶķĸĹĺĻļĽľĿ�����������������"};
const unsigned char PY_mb_na    []={"����������������������"};
const unsigned char PY_mb_nai   []={"����������ؾ٦ܵ����"};
const unsigned char PY_mb_nan   []={"����������������"};
const unsigned char PY_mb_nang  []={"��߭������"};
const unsigned char PY_mb_nao   []={"����������ث������������"};
const unsigned char PY_mb_ne    []={"��ګ��"};
const unsigned char PY_mb_nei   []={"����"};
const unsigned char PY_mb_nen   []={"���"};
const unsigned char PY_mb_neng  []={"��"};
const unsigned char PY_mb_ni    []={"������������������������٣�����������������"};
const unsigned char PY_mb_nian  []={"��������������إ���������"};
const unsigned char PY_mb_niang []={"����"};
const unsigned char PY_mb_niao  []={"������������"};
const unsigned char PY_mb_nie   []={"��������������ؿ����������"};
const unsigned char PY_mb_nin   []={"��"};
const unsigned char PY_mb_ning  []={"��������šŢ�������"};
const unsigned char PY_mb_niu   []={"ţŤťŦ�������"};
const unsigned char PY_mb_nong  []={"ũŪŧŨٯ��"};
const unsigned char PY_mb_nou   []={"��"};
const unsigned char PY_mb_nu    []={"ūŬŭ��������"};
const unsigned char PY_mb_nuan  []={"ů"};
const unsigned char PY_mb_nuo   []={"��ŲųŴŵ�������"};
const unsigned char PY_mb_nv    []={"Ů�����"};
const unsigned char PY_mb_nve   []={"Űű"};
const unsigned char PY_mb_o     []={"Ŷ���"};
const unsigned char PY_mb_ou    []={"ŷŸŹźŻżŽ��ک�����"};
const unsigned char PY_mb_pa    []={"�ǰ�žſ��������������"};
const unsigned char PY_mb_pai   []={"��������������ٽ����"};
const unsigned char PY_mb_pan   []={"�������������������������������������"};
const unsigned char PY_mb_pang  []={"����������������������"};
const unsigned char PY_mb_pao   []={"������������������������"};
const unsigned char PY_mb_pei   []={"�����������������������������"};
const unsigned char PY_mb_pen   []={"������"};
const unsigned char PY_mb_peng  []={"����������������������������ܡ�����"};
const unsigned char PY_mb_pi    []={"�ٷ�����������������ơƢƣƤƥƦƧƨƩا��������ۯ����ܱ��ߨ��������������������������"};
const unsigned char PY_mb_pian  []={"ƪƫƬƭ����������������"};
const unsigned char PY_mb_piao  []={"ƮƯưƱ����������������"};
const unsigned char PY_mb_pie   []={"ƲƳد���"};
const unsigned char PY_mb_pin   []={"ƴƵƶƷƸ�������"};
const unsigned char PY_mb_ping  []={"ƹƺƻƼƽƾƿ����ٷ����ҷ�"};
const unsigned char PY_mb_po    []={"��������������������������۶�����������"};
const unsigned char PY_mb_pou   []={"������"};
const unsigned char PY_mb_pu    []={"���������������������������������������������������"};
const unsigned char PY_mb_qi    []={"����������������������������������������������������������������������������ؽ��ٹ��ܻ��������ޭ�������������������������������������������"};
const unsigned char PY_mb_qia   []={"����ǡǢ������"};
const unsigned char PY_mb_qian  []={"ǣǤǥǦǧǨǩǪǫǬǭǮǯǰǱǲǳǴǵǶǷǸ��ٻ����ܷ����ݡ������������������������"};
const unsigned char PY_mb_qiang []={"ǹǺǻǼǽǾǿ�������������������������"};
const unsigned char PY_mb_qiao  []={"��������������������������������ȸ��ڽ������������������"};
const unsigned char PY_mb_qie   []={"����������٤ۧ�����������"};
const unsigned char PY_mb_qin   []={"��������������������������������������������"};
const unsigned char PY_mb_qing  []={"���������������������������������������������������"};
const unsigned char PY_mb_qiong []={"�����������������"};
const unsigned char PY_mb_qiu   []={"�������������������ٴ������������������������"};
const unsigned char PY_mb_qu    []={"����������������ȡȢȣȤȥ��ڰ۾����ޡ޾��������������������������"};
const unsigned char PY_mb_quan  []={"ȦȧȨȩȪȫȬȭȮȯȰڹ�����������������"};
const unsigned char PY_mb_que   []={"ȱȲȳȴȵȶȷȸ�����"};
const unsigned char PY_mb_qui   []={"��"};
const unsigned char PY_mb_qun   []={"ȹȺ����"};
const unsigned char PY_mb_ran   []={"ȻȼȽȾ������"};
const unsigned char PY_mb_rang  []={"ȿ�����������"};
const unsigned char PY_mb_rao   []={"�����������"};
const unsigned char PY_mb_re    []={"������"};
const unsigned char PY_mb_ren   []={"�����������������������������������"};
const unsigned char PY_mb_reng  []={"����"};
const unsigned char PY_mb_ri    []={"��"};
const unsigned char PY_mb_rong  []={"������������������������������"};
const unsigned char PY_mb_rou   []={"������������"};
const unsigned char PY_mb_ru    []={"����������������������޸������������"};
const unsigned char PY_mb_ruan  []={"������"};
const unsigned char PY_mb_rui   []={"��������ި����"};
const unsigned char PY_mb_run   []={"����"};
const unsigned char PY_mb_ruo   []={"����ټ��"};
const unsigned char PY_mb_sa    []={"������ئ�����"};
const unsigned char PY_mb_sai   []={"����������"};
const unsigned char PY_mb_san   []={"����ɡɢ�����"};
const unsigned char PY_mb_sang  []={"ɣɤɥ�����"};
const unsigned char PY_mb_sao   []={"ɦɧɨɩܣ��������"};
const unsigned char PY_mb_se    []={"��ɪɫɬ����"};
const unsigned char PY_mb_sen   []={"ɭ"};
const unsigned char PY_mb_seng  []={"ɮ"};
const unsigned char PY_mb_sha   []={"ɯɰɱɲɳɴɵɶɷɼ��������������"};
const unsigned char PY_mb_shai  []={"ɫɸɹ"};
const unsigned char PY_mb_shan  []={"����ɺɻɼɽɾɿ��������������������դ��ڨ۷������������������������������"};
const unsigned char PY_mb_shang []={"�������������������������"};
const unsigned char PY_mb_shao  []={"������������������������ۿ�����������"};
const unsigned char PY_mb_she   []={"�����������������������������������������"};
const unsigned char PY_mb_shei  []={"˭"};
const unsigned char PY_mb_shen  []={"����������������������������������ʲڷ��ݷ�������������"};
const unsigned char PY_mb_sheng []={"��������������ʡʢʣʤʥ����������"};
const unsigned char PY_mb_shi   []={"��ʦʧʨʩʪʫʬʭʮʯʰʱʲʳʴʵʶʷʸʹʺʻʼʽʾʿ��������������������������������������������ֳ������ݪ��߱��������������������������"};
const unsigned char PY_mb_shou  []={"���������������������������"};
const unsigned char PY_mb_shu   []={"����������������������������������������������������������������ˡحٿ����������������������"};
const unsigned char PY_mb_shua  []={"ˢˣ�"};
const unsigned char PY_mb_shuai []={"��ˤ˥˦˧�"};
const unsigned char PY_mb_shuan []={"˨˩����"};
const unsigned char PY_mb_shuang[]={"˪˫ˬ����"};
const unsigned char PY_mb_shui  []={"˭ˮ˯˰˵��"};
const unsigned char PY_mb_shun  []={"˱˲˳˴"};
const unsigned char PY_mb_shuo  []={"��˵˶˷˸����������"};
const unsigned char PY_mb_si    []={"˹˺˻˼˽˾˿��������������������ٹ�����������������������������"};
const unsigned char PY_mb_song  []={"����������������ڡݿ����������"};
const unsigned char PY_mb_sou   []={"����������޴�������������"};
const unsigned char PY_mb_su    []={"�����������������������������������������"};
const unsigned char PY_mb_suan  []={"�������"};
const unsigned char PY_mb_sui   []={"������������������������ݴ����������"};
const unsigned char PY_mb_sun   []={"������ݥ������"};
const unsigned char PY_mb_suo   []={"�������������������������������ɯ"};
const unsigned char PY_mb_ta    []={"����������̡̢̣̤������������������"};
const unsigned char PY_mb_tai   []={"̧̨̥̦̩̪̫̬̭ۢ޷������������"};
const unsigned char PY_mb_tan   []={"��̴̵̶̷̸̮̯̰̱̲̳̹̺̻̼̽̾̿۰��������������"};
const unsigned char PY_mb_tang  []={"�������������������������������������������������"};
const unsigned char PY_mb_tao   []={"����������������������ػ߶��������"};
const unsigned char PY_mb_te    []={"��߯���"};
const unsigned char PY_mb_teng  []={"����������"};
const unsigned char PY_mb_ti    []={"���������������������������������������������"};
const unsigned char PY_mb_tian  []={"����������������������������"};
const unsigned char PY_mb_tiao  []={"������������٬������������������"};
const unsigned char PY_mb_tie   []={"�����������"};
const unsigned char PY_mb_ting  []={"������ͣͤͥͦͧ͢͡��������������"};
const unsigned char PY_mb_tong  []={"ͨͩͪͫͬͭͮͯͰͱͲͳʹ١�����������������"};
const unsigned char PY_mb_tou   []={"͵Ͷͷ͸������"};
const unsigned char PY_mb_tu    []={"͹ͺͻͼͽ;Ϳ��������ܢݱ������"};
const unsigned char PY_mb_tuan  []={"���������"};
const unsigned char PY_mb_tui   []={"��������������"};
const unsigned char PY_mb_tun   []={"�����������������"};
const unsigned char PY_mb_tuo   []={"����������������������ر٢������������������������˵"};
const unsigned char PY_mb_wa    []={"�������������������"};
const unsigned char PY_mb_wai   []={"������"};
const unsigned char PY_mb_wan   []={"��������������������������������������ܹݸ��������������"};
const unsigned char PY_mb_wang  []={"�����������������������������"};
const unsigned char PY_mb_wei   []={"��Ρ΢ΣΤΥΦΧΨΩΪΫάέήίΰαβγδεζηθικλμνξο��������������ޱ���������������������������������"};
const unsigned char PY_mb_wen   []={"�������������������������������"};
const unsigned char PY_mb_weng  []={"��������޳"};
const unsigned char PY_mb_wo    []={"��������������������ݫ���������"};
const unsigned char PY_mb_wu    []={"������������������������������������������������������������أ����������������������������������������������"};
const unsigned char PY_mb_xi    []={"����������������������ϡϢϣϤϥϦϧϨϩϪϫϬϭϮϯϰϱϲϳϴϵ϶Ϸϸ��������ۭ��ݾ������������������������������������������������������������"};
const unsigned char PY_mb_xia   []={"ϹϺϻϼϽϾϿ���������������������������"};
const unsigned char PY_mb_xian  []={"ϳϴ��������������������������������������������������������ݲ޺������������������������������"};
const unsigned char PY_mb_xiang []={"����������������������������������������ܼ�������������Ͻ�"};
const unsigned char PY_mb_xiao  []={"����������������������СТУФХЦЧ���������������������"};
const unsigned char PY_mb_xie   []={"��ШЩЪЫЬЭЮЯабвгдежзийклмѪҶ��������ޯߢ���������������������"};
const unsigned char PY_mb_xin   []={"ноп��������������ضܰݷ��������"};
const unsigned char PY_mb_xing  []={"ʡ������������������������������������ߩ����"};
const unsigned char PY_mb_xiong []={"��������������ܺ"};
const unsigned char PY_mb_xiu   []={"������������������������������������"};
const unsigned char PY_mb_xu    []={"����������������������������������������ڼ����ޣ������������������"};
const unsigned char PY_mb_xuan  []={"������������ѡѢѣѤ����������������������������ȯ"};
const unsigned char PY_mb_xue   []={"ѥѦѧѨѩѪ�����������"};
const unsigned char PY_mb_xun   []={"��ѫѬѭѮѯѰѱѲѳѴѵѶѷѸ��ۨ����ݡަ޹���������������"};
const unsigned char PY_mb_ya    []={"ѹѺѻѼѽѾѿ������������������������������������������"};
const unsigned char PY_mb_yan   []={"��������������������������������������������������������������������������ٲ����ڥ����۱۳ܾ�������������������������������������������Ǧ"};
const unsigned char PY_mb_yang  []={"������������������������������������������������"};
const unsigned char PY_mb_yao   []={"����ű��������ҡҢңҤҥҦҧҨҩҪҫԿزسߺ��������������������������"};
const unsigned char PY_mb_ye    []={"��ҬҭҮүҰұҲҳҴҵҶҷҸҹҺ������������������а"};
const unsigned char PY_mb_yi    []={"��βһҼҽҾҿ������������������������������������������������������������������������������������������������������٫ڱ������ܲ����޲������߽߮�����������������������������������������������������������������"};
const unsigned char PY_mb_yin   []={"������������������������������ӡط۴����ܧ���������������������"};
const unsigned char PY_mb_ying  []={"ӢӣӤӥӦӧӨөӪӫӬӭӮӯӰӱӲӳ��۫����ݺ��������������������������"};
const unsigned char PY_mb_yo    []={"Ӵ���"};
const unsigned char PY_mb_yong  []={"ӵӶӷӸӹӺӻӼӽӾӿ��������ٸ��ܭ�����������"};
const unsigned char PY_mb_you   []={"��������������������������������������������٧ݬݯݵ��������������������������������"};
const unsigned char PY_mb_yu    []={"εξ������������������������������������������������������������������������������ԡԢԣԤԥԦخع��ٶ�������������������������������������������������������������������������������"};
const unsigned char PY_mb_yuan  []={"ԧԨԩԪԫԬԭԮԯ԰ԱԲԳԴԵԶԷԸԹԺܫܾ��������������������"};
const unsigned char PY_mb_yue   []={"ԻԼԽԾԿ������������������������˵"};
const unsigned char PY_mb_yun   []={"������������������������۩ܿ���������������Ա"};
const unsigned char PY_mb_za    []={"��������զ����"};
const unsigned char PY_mb_zai   []={"������������������"};
const unsigned char PY_mb_zan   []={"���������������������"};
const unsigned char PY_mb_zang  []={"�����������"};
const unsigned char PY_mb_zao   []={"������������������������������"};
const unsigned char PY_mb_ze    []={"��������զ�����������������"};
const unsigned char PY_mb_zei   []={"��"};
const unsigned char PY_mb_zen   []={"����"};
const unsigned char PY_mb_zeng  []={"��������������"};
const unsigned char PY_mb_zha   []={"������������աբգդեզէըթ����߸����������������"};
const unsigned char PY_mb_zhai  []={"����ժիլխծկ���"};
const unsigned char PY_mb_zhan  []={"��հձղճմյնշոչպջռսվտ���������"};
const unsigned char PY_mb_zhang []={"����������������������������������۵��������"};
const unsigned char PY_mb_zhao  []={"����������������������צ��گ��������"};
const unsigned char PY_mb_zhe   []={"������������������������ߡ��������������"};
const unsigned char PY_mb_zhen  []={"��������������������������������֡����������������������������"};
const unsigned char PY_mb_zheng []={"����������������������֢֣֤ں����������"};
const unsigned char PY_mb_zhi   []={"ʶְֱֲֳִֵֶַָֹֺֻּֽ֥֦֧֪֭֮֨֩֫֬֯־ֿ��������������������������������ش��ۤ����������������������������������������������������������������"};
const unsigned char PY_mb_zhong []={"����������������������ڣ���������"};
const unsigned char PY_mb_zhou  []={"����������������������������ݧ����������������"};
const unsigned char PY_mb_zhu   []={"������������������������������������������������סעףפؼ��٪ۥ������������������������������������"};
const unsigned char PY_mb_zhua  []={"��ץצ"};
const unsigned char PY_mb_zhuai []={"קת"};
const unsigned char PY_mb_zhuan []={"��רשת׫׬׭�������"};
const unsigned char PY_mb_zhuang[]={"��׮ׯװױײ׳״���"};
const unsigned char PY_mb_zhui  []={"׵׶׷׸׹׺�������"};
const unsigned char PY_mb_zhun  []={"׻׼����"};
const unsigned char PY_mb_zhuo  []={"׽׾׿����������������پ��ߪ�����������"};
const unsigned char PY_mb_zi    []={"֨����������������������������������������������������������������������"};
const unsigned char PY_mb_zong  []={"����������������������"};
const unsigned char PY_mb_zou   []={"������������۸����"};
const unsigned char PY_mb_zu    []={"����������������������"};
const unsigned char PY_mb_zuan  []={"����߬����"};
const unsigned char PY_mb_zui   []={"��������ީ��"};
const unsigned char PY_mb_zun   []={"����ߤ����"};
const unsigned char PY_mb_zuo   []={"������������������������������������"};

//**********************************************************************************************

/*"ƴ�����뷨��ѯ���,T9������ĸ������(index)"*/ 
t9PINYIN_INDEX  t9PinYin_Index2[]={ //--{"","",(pInt8U)PY_mb_space},//PY_mb_spaceΪ��
                                    {"2","a",(pInt8U)PY_mb_a},
                                    {"3","e",(pInt8U)PY_mb_e},
                                   //-- {"","i",(pInt8U)PY_mb_space},//PY_mb_spaceΪ��
                                    {"6","o",(pInt8U)PY_mb_o},
                                  //---  {"","u",(pInt8U)PY_mb_space},//PY_mb_spaceΪ��
                                 //--   {"","v",(pInt8U)PY_mb_space},//PY_mb_spaceΪ��
                                    {"24","ai",(pInt8U)PY_mb_ai},
                                    {"26","an",(pInt8U)PY_mb_an},
                                    {"26","ao",(pInt8U)PY_mb_ao},
                                    {"22","ba",(pInt8U)PY_mb_ba},
                                    {"24","bi",(pInt8U)PY_mb_bi},
                                    {"26","bo",(pInt8U)PY_mb_bo},
                                    {"28","bu",(pInt8U)PY_mb_bu},
                                    {"22","ca",(pInt8U)PY_mb_ca},
                                    {"23","ce",(pInt8U)PY_mb_ce},
                                    {"24","ci",(pInt8U)PY_mb_ci},
                                    {"28","cu",(pInt8U)PY_mb_cu},
                                    {"32","da",(pInt8U)PY_mb_da},
                                    {"33","de",(pInt8U)PY_mb_de},
                                    {"34","di",(pInt8U)PY_mb_di},
                                    {"38","du",(pInt8U)PY_mb_du},
                                    {"36","en",(pInt8U)PY_mb_en},
                                    {"37","er",(pInt8U)PY_mb_er},
                                    {"32","fa",(pInt8U)PY_mb_fa},
                                    {"36","fo",(pInt8U)PY_mb_fo},
                                    {"38","fu",(pInt8U)PY_mb_fu},
                                    {"42","ha",(pInt8U)PY_mb_ha},
                                    {"42","ga",(pInt8U)PY_mb_ga},
                                    {"43","ge",(pInt8U)PY_mb_ge},
                                    {"43","he",(pInt8U)PY_mb_he},
                                    {"48","gu",(pInt8U)PY_mb_gu},
                                    {"48","hu",(pInt8U)PY_mb_hu},
                                    {"54","ji",(pInt8U)PY_mb_ji},
                                    {"58","ju",(pInt8U)PY_mb_ju},
                                    {"52","ka",(pInt8U)PY_mb_ka},
                                    {"53","ke",(pInt8U)PY_mb_ke},
                                    {"58","ku",(pInt8U)PY_mb_ku},
                                    {"52","la",(pInt8U)PY_mb_la},
                                    {"53","le",(pInt8U)PY_mb_le},
                                    {"54","li",(pInt8U)PY_mb_li},
                                    {"58","lu",(pInt8U)PY_mb_lu},
                                    {"58","lv",(pInt8U)PY_mb_lv},
                                    {"62","ma",(pInt8U)PY_mb_ma},
                                    {"63","me",(pInt8U)PY_mb_me},
                                    {"64","mi",(pInt8U)PY_mb_mi},
                                    {"66","mo",(pInt8U)PY_mb_mo},
                                    {"68","mu",(pInt8U)PY_mb_mu},
                                    {"62","na",(pInt8U)PY_mb_na},
                                    {"63","ne",(pInt8U)PY_mb_ne},
                                    {"64","ni",(pInt8U)PY_mb_ni},
                                    {"68","nu",(pInt8U)PY_mb_nu},
                                    {"68","nv",(pInt8U)PY_mb_nv},
                                    {"68","ou",(pInt8U)PY_mb_ou},
                                    {"72","pa",(pInt8U)PY_mb_pa},
                                    {"74","pi",(pInt8U)PY_mb_pi},
                                    {"76","po",(pInt8U)PY_mb_po},
                                    {"78","pu",(pInt8U)PY_mb_pu},
                                    {"74","qi",(pInt8U)PY_mb_qi},
                                    {"78","qu",(pInt8U)PY_mb_qu},
                                    {"73","re",(pInt8U)PY_mb_re},
                                    {"74","ri",(pInt8U)PY_mb_ri},
                                    {"78","ru",(pInt8U)PY_mb_ru},
                                    {"72","sa",(pInt8U)PY_mb_sa},
                                    {"73","se",(pInt8U)PY_mb_se},
                                    {"74","si",(pInt8U)PY_mb_si},
                                    {"78","su",(pInt8U)PY_mb_su},
                                    {"82","ta",(pInt8U)PY_mb_ta},
                                    {"83","te",(pInt8U)PY_mb_te},
                                    {"84","ti",(pInt8U)PY_mb_ti},
                                    {"88","tu",(pInt8U)PY_mb_tu},
                                    {"92","wa",(pInt8U)PY_mb_wa},
                                    {"96","wo",(pInt8U)PY_mb_wo},
                                    {"98","wu",(pInt8U)PY_mb_wu},
                                    {"94","xi",(pInt8U)PY_mb_xi},
                                    {"98","xu",(pInt8U)PY_mb_xu},
                                    {"92","ya",(pInt8U)PY_mb_ya},
                                    {"93","ye",(pInt8U)PY_mb_ye},
                                    {"94","yi",(pInt8U)PY_mb_yi},
                                    {"96","yo",(pInt8U)PY_mb_yo},
                                    {"98","yu",(pInt8U)PY_mb_yu},
                                    {"92","za",(pInt8U)PY_mb_za},
                                    {"93","ze",(pInt8U)PY_mb_ze},
                                    {"94","zi",(pInt8U)PY_mb_zi},
                                    {"98","zu",(pInt8U)PY_mb_zu},
                                    {"264","ang",(pInt8U)PY_mb_ang},
                                    {"224","bai",(pInt8U)PY_mb_bai},
                                    {"226","ban",(pInt8U)PY_mb_ban},
                                    {"226","bao",(pInt8U)PY_mb_bao},
                                    {"234","bei",(pInt8U)PY_mb_bei},
                                    {"236","ben",(pInt8U)PY_mb_ben},
                                    {"243","bie",(pInt8U)PY_mb_bie},
                                    {"246","bin",(pInt8U)PY_mb_bin},
                                    {"224","cai",(pInt8U)PY_mb_cai},
                                    {"226","can",(pInt8U)PY_mb_can},
                                    {"226","cao",(pInt8U)PY_mb_cao},
                                    {"242","cha",(pInt8U)PY_mb_cha},
                                    {"243","che",(pInt8U)PY_mb_che},
                                    {"244","chi",(pInt8U)PY_mb_chi},
                                    {"248","chu",(pInt8U)PY_mb_chu},
                                    {"268","cou",(pInt8U)PY_mb_cou},
                                    {"284","cui",(pInt8U)PY_mb_cui},
                                    {"286","cun",(pInt8U)PY_mb_cun},
                                    {"286","cuo",(pInt8U)PY_mb_cuo},
                                    {"324","dai",(pInt8U)PY_mb_dai},
                                    {"326","dan",(pInt8U)PY_mb_dan},
                                    {"326","dao",(pInt8U)PY_mb_dao},
                                    {"343","die",(pInt8U)PY_mb_die},
                                    {"348","diu",(pInt8U)PY_mb_diu},
                                    {"368","dou",(pInt8U)PY_mb_dou},
                                    {"384","dui",(pInt8U)PY_mb_dui},
                                    {"386","dun",(pInt8U)PY_mb_dun},
                                    {"386","duo",(pInt8U)PY_mb_duo},
                                    {"326","fan",(pInt8U)PY_mb_fan},
                                    {"334","fei",(pInt8U)PY_mb_fei},
                                    {"336","fen",(pInt8U)PY_mb_fen},
                                    {"368","fou",(pInt8U)PY_mb_fou},
                                    {"424","gai",(pInt8U)PY_mb_gai},
                                    {"426","gan",(pInt8U)PY_mb_gan},
                                    {"426","gao",(pInt8U)PY_mb_gao},
                                    {"434","gei",(pInt8U)PY_mb_gei},
                                    {"436","gen",(pInt8U)PY_mb_gan},
                                    {"468","gou",(pInt8U)PY_mb_gou},
                                    {"482","gua",(pInt8U)PY_mb_gua},
                                    {"484","gui",(pInt8U)PY_mb_gui},
                                    {"486","gun",(pInt8U)PY_mb_gun},
                                    {"486","guo",(pInt8U)PY_mb_guo},
                                    {"423","hai",(pInt8U)PY_mb_hai},
                                    {"426","han",(pInt8U)PY_mb_han},
                                    {"426","hao",(pInt8U)PY_mb_hao},
                                    {"434","hei",(pInt8U)PY_mb_hei},
                                    {"436","hen",(pInt8U)PY_mb_hen},
                                    {"468","hou",(pInt8U)PY_mb_hou},
                                    {"482","hua",(pInt8U)PY_mb_hua},
                                    {"484","hui",(pInt8U)PY_mb_hui},
                                    {"486","hun",(pInt8U)PY_mb_hun},
                                    {"486","huo",(pInt8U)PY_mb_huo},
                                    {"542","jia",(pInt8U)PY_mb_jia},
                                    {"543","jie",(pInt8U)PY_mb_jie},
                                    {"546","jin",(pInt8U)PY_mb_jin},
                                    {"548","jiu",(pInt8U)PY_mb_jiu},
                                    {"583","jue",(pInt8U)PY_mb_jue},
                                    {"586","jun",(pInt8U)PY_mb_jun},
                                    {"524","kai",(pInt8U)PY_mb_kai},
                                    {"526","kan",(pInt8U)PY_mb_kan},
                                    {"526","kao",(pInt8U)PY_mb_kao},
                                    {"536","ken",(pInt8U)PY_mb_ken},
                                    {"568","kou",(pInt8U)PY_mb_kou},
                                    {"582","kua",(pInt8U)PY_mb_kua},
                                    {"584","kui",(pInt8U)PY_mb_kui},
                                    {"586","kun",(pInt8U)PY_mb_kun},
                                    {"586","kuo",(pInt8U)PY_mb_kuo},
                                    {"524","lai",(pInt8U)PY_mb_lai},
                                    {"526","lan",(pInt8U)PY_mb_lan},
                                    {"526","lao",(pInt8U)PY_mb_lao},
                                    {"534","lei",(pInt8U)PY_mb_lei},
                                    {"543","lie",(pInt8U)PY_mb_lie},
                                    {"546","lin",(pInt8U)PY_mb_lin},
                                    {"548","liu",(pInt8U)PY_mb_liu},
                                    {"568","lou",(pInt8U)PY_mb_lou},
                                    {"583","lue",(pInt8U)PY_mb_lve},
                                    {"586","lun",(pInt8U)PY_mb_lun},
                                    {"586","luo",(pInt8U)PY_mb_luo},
                                    {"624","mai",(pInt8U)PY_mb_mai},
                                    {"626","man",(pInt8U)PY_mb_man},
                                    {"626","mao",(pInt8U)PY_mb_mao},
                                    {"634","mei",(pInt8U)PY_mb_mei},
                                    {"636","men",(pInt8U)PY_mb_men},
                                    {"643","mie",(pInt8U)PY_mb_mie},
                                    {"646","min",(pInt8U)PY_mb_min},
                                    {"648","miu",(pInt8U)PY_mb_miu},
                                    {"668","mou",(pInt8U)PY_mb_mou},
                                    {"624","nai",(pInt8U)PY_mb_nai},
                                    {"626","nan",(pInt8U)PY_mb_nan},
                                    {"626","nao",(pInt8U)PY_mb_nao},
                                    {"634","nei",(pInt8U)PY_mb_nei},
                                    {"636","nen",(pInt8U)PY_mb_nen},
                                    {"643","nie",(pInt8U)PY_mb_nie},
                                    {"646","nin",(pInt8U)PY_mb_nin},
                                    {"648","niu",(pInt8U)PY_mb_niu},
                                    {"683","nue",(pInt8U)PY_mb_nve},
                                    {"686","nuo",(pInt8U)PY_mb_nuo},
                                    {"724","pai",(pInt8U)PY_mb_pai},
                                    {"726","pan",(pInt8U)PY_mb_pan},
                                    {"726","pao",(pInt8U)PY_mb_pao},
                                    {"734","pei",(pInt8U)PY_mb_pei},
                                    {"736","pen",(pInt8U)PY_mb_pen},
                                    {"743","pie",(pInt8U)PY_mb_pie},
                                    {"746","pin",(pInt8U)PY_mb_pin},
                                    {"768","pou",(pInt8U)PY_mb_pou},
                                    {"742","qia",(pInt8U)PY_mb_qia},
                                    {"743","qie",(pInt8U)PY_mb_qie},
                                    {"746","qin",(pInt8U)PY_mb_qin},
                                    {"748","qiu",(pInt8U)PY_mb_qiu},
                                    {"783","que",(pInt8U)PY_mb_que},
                                    {"786","qun",(pInt8U)PY_mb_qun},
                                    {"726","ran",(pInt8U)PY_mb_ran},
                                    {"726","rao",(pInt8U)PY_mb_rao},
                                    {"736","ren",(pInt8U)PY_mb_ren},
                                    {"768","rou",(pInt8U)PY_mb_rou},
                                    {"784","rui",(pInt8U)PY_mb_rui},
                                    {"786","run",(pInt8U)PY_mb_run},
                                    {"786","ruo",(pInt8U)PY_mb_ruo},
                                    {"724","sai",(pInt8U)PY_mb_sai},
                                    {"726","sao",(pInt8U)PY_mb_sao},
                                    {"726","san",(pInt8U)PY_mb_san},
                                    {"736","sen",(pInt8U)PY_mb_sen},
                                    {"742","sha",(pInt8U)PY_mb_sha},
                                    {"743","she",(pInt8U)PY_mb_she},
                                    {"744","shi",(pInt8U)PY_mb_shi},
                                    {"748","shu",(pInt8U)PY_mb_shu},
                                    {"768","sou",(pInt8U)PY_mb_sou},
                                    {"784","sui",(pInt8U)PY_mb_sui},
                                    {"786","sun",(pInt8U)PY_mb_sun},
                                    {"786","suo",(pInt8U)PY_mb_suo},
                                    {"824","tai",(pInt8U)PY_mb_tai},
                                    {"826","tan",(pInt8U)PY_mb_tan},
                                    {"826","tao",(pInt8U)PY_mb_tao},
                                    {"843","tie",(pInt8U)PY_mb_tie},
                                    {"868","tou",(pInt8U)PY_mb_tou},
                                    {"884","tui",(pInt8U)PY_mb_tui},
                                    {"886","tun",(pInt8U)PY_mb_tun},
                                    {"886","tuo",(pInt8U)PY_mb_tuo},
                                    {"924","wai",(pInt8U)PY_mb_wai},
                                    {"926","wan",(pInt8U)PY_mb_wan},
                                    {"934","wei",(pInt8U)PY_mb_wei},
                                    {"936","wen",(pInt8U)PY_mb_wen},
                                    {"942","xia",(pInt8U)PY_mb_xia},
                                    {"943","xie",(pInt8U)PY_mb_xie},
                                    {"946","xin",(pInt8U)PY_mb_xin},
                                    {"948","xiu",(pInt8U)PY_mb_xiu},
                                    {"983","xue",(pInt8U)PY_mb_xue},
                                    {"986","xun",(pInt8U)PY_mb_xun},
                                    {"926","yan",(pInt8U)PY_mb_yan},
                                    {"926","yao",(pInt8U)PY_mb_yao},
                                    {"946","yin",(pInt8U)PY_mb_yin},
                                    {"968","you",(pInt8U)PY_mb_you},
                                    {"983","yue",(pInt8U)PY_mb_yue},
                                    {"986","yun",(pInt8U)PY_mb_yun},
                                    {"924","zai",(pInt8U)PY_mb_zai},
                                    {"926","zan",(pInt8U)PY_mb_zan},
                                    {"926","zao",(pInt8U)PY_mb_zao},
                                    {"934","zei",(pInt8U)PY_mb_zei},
                                    {"936","zen",(pInt8U)PY_mb_zen},
                                    {"942","zha",(pInt8U)PY_mb_zha},
                                    {"943","zhe",(pInt8U)PY_mb_zhe},
                                    {"944","zhi",(pInt8U)PY_mb_zhi},
                                    {"948","zhu",(pInt8U)PY_mb_zhu},
                                    {"968","zou",(pInt8U)PY_mb_zou},
                                    {"984","zui",(pInt8U)PY_mb_zui},
                                    {"986","zun",(pInt8U)PY_mb_zun},
                                    {"986","zuo",(pInt8U)PY_mb_zuo},
                                    {"2264","bang",(pInt8U)PY_mb_bang},
                                    {"2364","beng",(pInt8U)PY_mb_beng},
                                    {"2426","bian",(pInt8U)PY_mb_bian},
                                    {"2426","biao",(pInt8U)PY_mb_biao},
                                    {"2464","bing",(pInt8U)PY_mb_bing},
                                    {"2264","cang",(pInt8U)PY_mb_cang},
                                    {"2364","ceng",(pInt8U)PY_mb_ceng},
                                    {"2424","chai",(pInt8U)PY_mb_chai},
                                    {"2426","chan",(pInt8U)PY_mb_chan},
                                    {"2426","chao",(pInt8U)PY_mb_chao},
                                    {"2436","chen",(pInt8U)PY_mb_chen},
                                    {"2468","chou",(pInt8U)PY_mb_chou},
                                    //----{"248424","chuai",(pInt8U)PY_mb_chuai},
                                    {"2484","chui",(pInt8U)PY_mb_chui},
                                    {"2484","chun",(pInt8U)PY_mb_chun},
                                    {"2486","chuo",(pInt8U)PY_mb_chuo},
                                    {"2664","cong",(pInt8U)PY_mb_cong},
                                    {"2826","cuan",(pInt8U)PY_mb_cuan},
                                    {"3264","dang",(pInt8U)PY_mb_dang},
                                    {"3364","deng",(pInt8U)PY_mb_deng},
                                    {"3426","dian",(pInt8U)PY_mb_dian},
                                    {"3426","diao",(pInt8U)PY_mb_diao},
                                    {"3464","ding",(pInt8U)PY_mb_ding},
                                    {"3664","dong",(pInt8U)PY_mb_dong},
                                    {"3826","duan",(pInt8U)PY_mb_duan},
                                    {"3264","fang",(pInt8U)PY_mb_fang},
                                    {"3364","feng",(pInt8U)PY_mb_feng},
                                    {"4264","gang",(pInt8U)PY_mb_gang},
                                    {"4364","geng",(pInt8U)PY_mb_geng},
                                    {"4664","gong",(pInt8U)PY_mb_gong},
                                    {"4824","guai",(pInt8U)PY_mb_guai},
                                    {"4826","guan",(pInt8U)PY_mb_guan},
                                    {"4264","hang",(pInt8U)PY_mb_hang},
                                    {"4364","heng",(pInt8U)PY_mb_heng},
                                    {"4664","hong",(pInt8U)PY_mb_hong},
                                    {"4823","huai",(pInt8U)PY_mb_huai},
                                    {"4826","huan",(pInt8U)PY_mb_huan},
                                    {"5426","jian",(pInt8U)PY_mb_jian},
                                    {"5426","jiao",(pInt8U)PY_mb_jiao},
                                    {"5464","jing",(pInt8U)PY_mb_jing},
                                    {"5826","juan",(pInt8U)PY_mb_juan},
                                    {"5264","kang",(pInt8U)PY_mb_kang},
                                    {"5364","keng",(pInt8U)PY_mb_keng},
                                    {"5664","kong",(pInt8U)PY_mb_kong},
                                    {"5824","kuai",(pInt8U)PY_mb_kuai},
                                    {"5826","kuan",(pInt8U)PY_mb_kuan},
                                    {"5264","lang",(pInt8U)PY_mb_lang},
                                    {"5366","leng",(pInt8U)PY_mb_leng},
                                    {"5426","lian",(pInt8U)PY_mb_lian},
                                    {"5426","liao",(pInt8U)PY_mb_liao},
                                    {"5464","ling",(pInt8U)PY_mb_ling},
                                    {"5664","long",(pInt8U)PY_mb_long},
                                    {"5826","luan",(pInt8U)PY_mb_luan},
                                    {"6264","mang",(pInt8U)PY_mb_mang},
                                    {"6364","meng",(pInt8U)PY_mb_meng},
                                    {"6426","mian",(pInt8U)PY_mb_mian},
                                    {"6426","miao",(pInt8U)PY_mb_miao},
                                    {"6464","ming",(pInt8U)PY_mb_ming},
                                    {"6264","nang",(pInt8U)PY_mb_nang},
                                    {"6364","neng",(pInt8U)PY_mb_neng},
                                    {"6426","nian",(pInt8U)PY_mb_nian},
                                    {"6426","niao",(pInt8U)PY_mb_niao},
                                    {"6464","ning",(pInt8U)PY_mb_ning},
                                    {"6664","nong",(pInt8U)PY_mb_nong},
                                    {"6826","nuan",(pInt8U)PY_mb_nuan},
                                    {"7264","pang",(pInt8U)PY_mb_pang},
                                    {"7364","peng",(pInt8U)PY_mb_peng},
                                    {"7426","pian",(pInt8U)PY_mb_pian},
                                    {"7426","piao",(pInt8U)PY_mb_piao},
                                    {"7464","ping",(pInt8U)PY_mb_ping},
                                    {"7426","qian",(pInt8U)PY_mb_qian},
                                    {"7426","qiao",(pInt8U)PY_mb_qiao},
                                    {"7464","qing",(pInt8U)PY_mb_qing},
                                    {"7826","quan",(pInt8U)PY_mb_quan},
                                    {"7264","rang",(pInt8U)PY_mb_rang},
                                    {"7364","reng",(pInt8U)PY_mb_reng},
                                    {"7664","rong",(pInt8U)PY_mb_rong},
                                    {"7826","ruan",(pInt8U)PY_mb_ruan},
                                    {"7264","sang",(pInt8U)PY_mb_sang},
                                    {"7364","seng",(pInt8U)PY_mb_seng},
                                    {"7424","shai",(pInt8U)PY_mb_shai},
                                    {"7426","shan",(pInt8U)PY_mb_shan},
                                    {"7426","shao",(pInt8U)PY_mb_shao},
                                    {"7436","shen",(pInt8U)PY_mb_shen},
                                    {"7468","shou",(pInt8U)PY_mb_shou},
                                    {"7482","shua",(pInt8U)PY_mb_shua},
                                    {"7484","shui",(pInt8U)PY_mb_shui},
                                    {"7486","shun",(pInt8U)PY_mb_shun},
                                    {"7486","shuo",(pInt8U)PY_mb_shuo},
                                    {"7664","song",(pInt8U)PY_mb_song},
                                    {"7826","suan",(pInt8U)PY_mb_suan},
                                    {"8264","tang",(pInt8U)PY_mb_tang},
                                    {"8364","teng",(pInt8U)PY_mb_teng},
                                    {"8426","tian",(pInt8U)PY_mb_tian},
                                    {"8426","tiao",(pInt8U)PY_mb_tiao},
                                    {"8464","ting",(pInt8U)PY_mb_ting},
                                    {"8664","tong",(pInt8U)PY_mb_tong},
                                    {"8826","tuan",(pInt8U)PY_mb_tuan},
                                    {"9264","wang",(pInt8U)PY_mb_wang},
                                    {"9364","weng",(pInt8U)PY_mb_weng},
                                    {"9426","xian",(pInt8U)PY_mb_xiao},
                                    {"9426","xiao",(pInt8U)PY_mb_xiao},
                                    {"9464","xing",(pInt8U)PY_mb_xing},
                                    {"9826","xuan",(pInt8U)PY_mb_xuan},
                                    {"9264","yang",(pInt8U)PY_mb_yang},
                                    {"9464","ying",(pInt8U)PY_mb_ying},
                                    {"9664","yong",(pInt8U)PY_mb_yong},
                                    {"9826","yuan",(pInt8U)PY_mb_yuan},
                                    {"9264","zang",(pInt8U)PY_mb_zang},
                                    {"9364","zeng",(pInt8U)PY_mb_zeng},
                                    {"9424","zhai",(pInt8U)PY_mb_zhai},
                                    {"9426","zhan",(pInt8U)PY_mb_zhan},
                                    {"9426","zhao",(pInt8U)PY_mb_zhao},
                                    {"9436","zhen",(pInt8U)PY_mb_zhen},
                                    {"9468","zhou",(pInt8U)PY_mb_zhou},
                                    {"9482","zhua",(pInt8U)PY_mb_zhua},
                                    {"9484","zhui",(pInt8U)PY_mb_zhui},
                                    {"9486","zhun",(pInt8U)PY_mb_zhun},
                                    {"9486","zhuo",(pInt8U)PY_mb_zhuo},
                                    {"9664","zong",(pInt8U)PY_mb_zong},
                                    {"9826","zuan",(pInt8U)PY_mb_zuan},
                                    {"24264","chang",(pInt8U)PY_mb_chang},
                                    {"24364","cheng",(pInt8U)PY_mb_cheng},
                                    {"24664","chong",(pInt8U)PY_mb_chong},
                                    {"24824","chuai",(pInt8U)PY_mb_chuai},
                                    {"24826","chuan",(pInt8U)PY_mb_chuan},
                                    {"48264","guang",(pInt8U)PY_mb_guang},
                                    {"48264","huang",(pInt8U)PY_mb_huang},
                                    {"54264","jiang",(pInt8U)PY_mb_jiang},
                                    {"54664","jiong",(pInt8U)PY_mb_jiong},
                                    {"58264","kuang",(pInt8U)PY_mb_kuang},
                                    {"54264","liang",(pInt8U)PY_mb_liang},
                                    {"64264","niang",(pInt8U)PY_mb_niang},
                                    {"74264","qiang",(pInt8U)PY_mb_qiang},
                                    {"74664","qiong",(pInt8U)PY_mb_qiong},
                                    {"74264","shang ",(pInt8U)PY_mb_shang},
                                    {"74364","sheng",(pInt8U)PY_mb_sheng},
                                    {"74824","shuai",(pInt8U)PY_mb_shuai},
                                    {"74826","shuan",(pInt8U)PY_mb_shuan},
                                    {"94264","xiang",(pInt8U)PY_mb_xiang},
                                    {"94664","xiong",(pInt8U)PY_mb_xiong},
                                    {"94264","zhang",(pInt8U)PY_mb_zhang},
                                    {"94364","zheng",(pInt8U)PY_mb_zheng},
                                    {"94664","zhong",(pInt8U)PY_mb_zhong},
                                    {"94824","zhuai",(pInt8U)PY_mb_zhuai},
                                    {"94826","zhuan",(pInt8U)PY_mb_zhuan},
                                    {"248264","chuang",(pInt8U)PY_mb_chuang},
                                    {"748264","shuang",(pInt8U)PY_mb_shuang},
                                    {"948264","zhuang",(pInt8U)PY_mb_zhuang}
								}; 

t9PINYIN_INDEX *List_match_PY_Mb[INDEX_SIZE];

//========================================================================
//	�﷨��ʽ��	unsigned char T9PY_Get_Match_PY_MB(unsigned char *pInputStr, Int8U len)	
//	ʵ�ֹ��ܣ�	��ȡ��������ƥ���T9ƴ���б�
//	������		p_PadInput	����İ������У���'0'~'9'��ɵ��ַ���
//				List_match_PY_Mb	�洢"��ȡ����ƴ��������ַ"������
//	����ֵ��	��ȡ����ȫƥ��ƴ������
//  ��ֲע�⣺	List_match_PY_Mb��ָ��Ĵ洢�ṹ,�����ڴ��ƥ���ƴ������ַ�Ĵ洢�ṹ.
//				��һ��Ԫ�ش�ŵ���һ����ƥ���ƴ������ַ.����Ϊƥ���ƴ������ַ
//========================================================================
Int8U T9PY_Get_Match_PY_MB(unsigned char *pInputStr, Int8U len)		//
{
/******
//===========================	����һ	(��ֲ���е�)=============================
Int8U n=0;
Int16U array_sum;
t9PINYIN_INDEX	*pPY_currentIndex,*pPY_lastIndex;
Int8U index_cou=0;

//------------����pInputStr����
// Int8U len=0;
// while(pInputStr[len]!='\0')
	// {
	// len++;
	// }
//----------����������t9PinYin_Index2Ԫ�ظ������Եõ�����Ԫ�ص�ַ
array_sum=sizeof(t9PinYin_Index2)/sizeof(t9PinYin_Index2[0]);
pPY_currentIndex=t9PinYin_Index2;
pPY_lastIndex=t9PinYin_Index2+array_sum;
//---------------
while(pPY_currentIndex<pPY_lastIndex)
	{
	while(n<len)
		{
		if(*(pInputStr+n)==*((*pPY_currentIndex).nums_str+n))
			n++;
		else
			break;
		}
	if(n==len)	//ƥ��	
		{
		if(index_cou<INDEX_SIZE)	//ƥ������ δ��������
			{
			List_match_PY_Mb[index_cou++]=pPY_currentIndex;	//index ָ�� ����buf 
			}
		}
		
	pPY_currentIndex++;		//��һ����
	n=0;
	}
*************/
//=====================================���� �������ݷ���һ�Լ����˾����㷨��===============
Int16U array_sum, t=0;
Int16U n=0;
pInt8U ptemp;
Int8U index_cou=0;
//----------����������t9PinYin_Index2Ԫ�ظ������Եõ�����Ԫ�ص�ַ
array_sum=sizeof(t9PinYin_Index2)/sizeof(t9PinYin_Index2[0]);
while(t<array_sum)
	{
	ptemp=(pInt8U)&t9PinYin_Index2[t];
	while(n<len)
		{
		if(*(pInputStr+n)==*(ptemp+n))
			n++;
		else
			break;
		}
	if(n==len)	//ƥ��	
		{
		if(index_cou<INDEX_SIZE)	//ƥ������ δ��������
			{
			// List_match_PY_Mb[index_cou++]=(t9PINYIN_INDEX *)ptemp;	//����buf
			List_match_PY_Mb[index_cou++]=&t9PinYin_Index2[t];	//����buf��ͬ�ϣ�
			}
		}
	n=0;	
	t++;
	}

//-----------------
return 	index_cou;//ƥ������
}

