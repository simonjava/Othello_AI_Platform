<%@page import="com.csm.webUtil.common.MsgUtil"%>
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@page import="com.platform.entity.Replay"%>
<%@page import="com.platform.operator.ReplayOperator"%>


<%
	String id = (String) session.getAttribute("id");
	String replay_id = (String) request.getParameter("replay_id");
	Replay re = null;
	if (replay_id != null && !"".equals(replay_id))
	{
		re = ReplayOperator.getReplayById(Integer.parseInt(replay_id));
		if (!re.getPlayer1().equals(id) && !re.getPlayer2().equals(id))
		{
			MsgUtil.showDialog(response, "limits of authority",
					"main.jsp");
		}
	} else
	{
		MsgUtil.showDialog(response, "Illegal Request", "main.jsp");
	}
%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<title>比赛回放</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<style type="text/css" media="screen">
html,body {
	height: 100%;
	background-color: #cccccc;
}

body {
	margin: 0;
	padding: 0;
	overflow: hidden;
}

#flashContent {
	width: 100%;
	height: 100%;
}
</style>
</head>
<body>

	<center>
	<h1>
		<%
			if ("wait contest".equals(re.getStatus()))
			{
		%>
		Waiting for the start of the game,please refresh later
		<%
			} else if ("contesting".equals(re.getStatus()))
			{
		%>
		Game in progress,please refresh later
		<%
			} else if ("contest over".equals(re.getStatus()))
			{
		%>
		Contest over,you can watch the replay
		<%
			}else if ("enter queue".equals(re.getStatus()))
			{
		%>
		Has entered contest queue,please wait and refresh later
		<%} %>
	</h1>
	<%
		if ("contest over".equals(re.getStatus()))
		{
	%>
	<div id="flashContent">
		<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000"
			width="670" height="500" id="contest" align="middle">
			<param name="movie" value="flash/contest.swf" />
			<param name="quality" value="high" />
			<param name="bgcolor" value="#cccccc" />
			<param name="play" value="true" />
			<param name="loop" value="true" />
			<param name="wmode" value="window" />
			<param name="scale" value="showall" />
			<param name="menu" value="true" />
			<param name="devicefont" value="false" />
			<param name="salign" value="" />
			<param name="allowScriptAccess" value="sameDomain" />
			<param name="flashvars"
				value="player1=<%=re.getPlayer1()%>&player2=<%=re.getPlayer2()%>&winner=<%=re.getWinner()%>&pro=<%=re.getProcess()%>" />
			<!--[if !IE]>-->
			<object type="application/x-shockwave-flash" data="flash/contest.swf"
				width="670" height="500">
				<param name="movie" value="flash/first.swf" />
				<param name="quality" value="high" />
				<param name="bgcolor" value="#cccccc" />
				<param name="play" value="true" />
				<param name="loop" value="true" />
				<param name="wmode" value="window" />
				<param name="scale" value="showall" />
				<param name="menu" value="true" />
				<param name="devicefont" value="false" />
				<param name="salign" value="" />
				<param name="allowScriptAccess" value="sameDomain" />
				<param name="flashvars"
					value="player1=<%=re.getPlayer1()%>&player2=<%=re.getPlayer2()%>&winner=<%=re.getWinner()%>&pro=<%=re.getProcess()%>" />
				<!--<![endif]-->
				<a href="http://www.adobe.com/go/getflash"> <img
					src="http://www.adobe.com/images/shared/download_buttons/get_flash_player.gif"
					alt="获得 Adobe Flash Player" /> </a>
				<!--[if !IE]>-->
			</object>
			<!--<![endif]-->
		</object>
	</div>
	<%
		}
	%> </center>
</body>
</html>