#ifndef __JTXDWEB_H
#define __JTXDWEB_H
#define JTXD_WEB  "<!DOCTYPE html>"\
"<html>"\
"<head>"\
"<title>清晨的网页配置</title>"\
"<meta http-equiv='Content-Type' content='text/html; charset=GB2312'/>"\
"<style type='text/css'>"\
"body {text-align:left; background-color:#c0deed;font-family:Verdana;}"\
"#main {margin-right:auto;margin-left:auto;margin-top:10px;}"\
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
"<div style='background:snow; display:block;padding:20px 50px;'>"\
"<h3 align='center'>配置网络参数</h3>"\
"<form id='frmSetting' method='POST' action='config.cgi'>"\
"<p><label for='txtIp'>固件版本号:</label><input type='text' id='txtVer' name='ver' size='16' disabled='disabled' /></p>"\
"<p><label for='txtIp'>MAC地址:</label><input type='text' id='txtMac' name='mac' size='16' disabled='disabled' /></p>"\
"<p style='color:DarkBlue'><label for='txtIp'>IP地址:</label><input type='text' id='txtIp' name='ip' size='16' /></p>"\
"<p style='color:DarkBlue'><label for='txtSub'>子网掩码:</label><input type='text' id='txtSub' name='sub' size='16' /></p>"\
"<p style='color:DarkBlue'><label for='txtGw'>默认网关:</label><input type='text' id ='txtGw' name='gw' size='16' /></p>"\
\
"<p style='color:DarkBlue'><label for='txtCode'>行政编码:</label><input type='text' id='txtCode' name='Code' size='16' /></p>"\
"<p style='color:DarkBlue'><label for='txtDTMB_Freq'>DTMB频率:</label><input type='text' id='txtDTMB_Freq' name='DTMB_Freq' size='16' /></p>"\
"<p style='color:DarkBlue'><label for='txtFM_Freq'>调频频率:</label><input type='text' id='txtFM_Freq' name='FM_Freq' size='16' /></p>"\
"<p style='color:DarkBlue'><label for='txtSx_Freq'>无线频率:</label><input type='text' id='txtSx_Freq' name='Sx_Freq' size='16' /></p>"\
"<h4 align='left'>请注意：需修改密码才填写下面带*号选项</h4>"\
"<p style='color:OrangeRed'><label for='txtPassword'>*输入原密码:</label><input type='password' id='txtPassword' name='Password' size='16' /></p>"\
"<p style='color:OrangeRed'><label for='txtNew_Password'>*新密码(6位数字):</label><input type='password' id='txtNew_Password' name='New_Password' size='16' /></p>"\
"<p style='color:OrangeRed'><label for='txtY_New_Password'>*确认修改密码:</label><input type='password' id='txtY_New_Password' name='Y_New_Password' size='16' /></p>"\
"<p><input type='submit' value=' 保存并重启 ' /></p>"\
"<p><input type='submit' value=' 退  出 ' name='close' /></p>"\
\
"</form>"\
"</div>"\
"</div>"\
"<div style='margin:5px 5px;'>"\
"&copy;Copyright 2017 by 清晨"\
"</div>"\
"<script type='text/javascript' src='w5500.js'></script>"\
"</body>"\
"</html>"

/*"*/

#endif
