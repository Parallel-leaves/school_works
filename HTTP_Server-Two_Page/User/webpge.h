#ifndef __WEBPAGE_H
#define __WEBPAGE_H
#define INDEX_HTML  "<!DOCTYPE html>"\
"<html>"\
"<head>"\
"<title>�峿����ҳ����</title>"\
"<meta http-equiv='Content-Type' content='text/html; charset=GB2312'/>"\
"<style type='text/css'>"\
"body {text-align:left; background-color:#c0deed;font-family:Verdana;}"\
"#main {margin-right:auto;margin-left:auto;margin-top:30px;}"\
"label{display:inline-block;width:150px;}"\
"#main h3{color:#66b3ff; text-decoration:underline;}"\
"</style>"\
"<script>"\
"function $(id) { return document.getElementById(id); };"\
"function settingsCallback(o) {"\
"if ($('txtVer')) $('txtVer').value = o.ver;"\
"if ($('txtMac')) $('txtMac').value = o.mac;"\
"if ($('txtIp')) $('txtIp').value = o.ip;"\
"if ($('txtSub')) $('txtSub').value = o.sub;"\
"if ($('txtGw')) $('txtGw').value = o.gw;"\
\
"if ($('txtCode')) $('txtCode').value = o.Code;"\
"if ($('txtDTMB_Freq')) $('txtDTMB_Freq').value = o.DTMB_Freq;"\
"if ($('txtFM_Freq')) $('txtFM_Freq').value = o.FM_Freq;"\
"if ($('txtSx_Freq')) $('txtSx_Freq').value = o.Sx_Freq;"\
\
"};"\
"</script>"\
"</head>"\
"<body>"\
"<div id='main'>"\
"<div style='background:snow; display:block;padding:10px 20px;'>"\
"<h3 align='center'>�鿴�������</h3>"\
"<form id='frmSetting' method='POST' action='config.cgi'>"\
"<p><label for='txtIp'>�̼��汾��:</label><input type='text' id='txtVer' name='ver' size='16' disabled='disabled' /></p>"\
"<p><label for='txtIp'>MAC��ַ:</label><input type='text' id='txtMac' name='mac' size='16' disabled='disabled' /></p>"\
"<p><label for='txtIp'>IP��ַ:</label><input type='text' id='txtIp' name='ip' size='16' disabled='disabled'/></p>"\
"<p><label for='txtSub'>��������:</label><input type='text' id='txtSub' name='sub' size='16' disabled='disabled'/></p>"\
"<p><label for='txtGw'>Ĭ������:</label><input type='text' id='txtGw' name='gw' size='16' disabled='disabled'/></p>"\
\
"<p><label for='txtCode'>��������:</label><input type='text' id='txtCode' name='Code' size='16' disabled='disabled'/></p>"\
"<p><label for='txtDTMB_Freq'>DTMBƵ��:</label><input type='text' id='txtDTMB_Freq' name='DTMB_Freq' size='16' disabled='disabled' /></p>"\
"<p><label for='txtFM_Freq'>��ƵƵ��:</label><input type='text' id='txtFM_Freq' name='FM_Freq' size='16' disabled='disabled'/></p>"\
"<p><label for='txtSx_Freq'>����Ƶ��:</label><input type='text' id='txtSx_Freq' name='Sx_Freq' size='16' disabled='disabled' /></p>"\
"<p style='color:DarkBlue'><label for='txtPassword'>��¼����6λ:</label><input type='password' id='txtPassword' name='Password' size='16' enabled='enabled'/></p>"\
"<input type='submit' value=' ��  ¼ ' /></p>"\
\
"</form>"\
"</div>"\
"</div>"\
"<div style='margin:5px 5px;'>"\
"&copy;Copyright 2017 by �峿"\
"</div>"\
"<script type='text/javascript' src='w5500.js'></script>"\
"</body>"\
"</html>"

#endif
