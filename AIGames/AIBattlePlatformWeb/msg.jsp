<%@page import="com.platform.entity.Task"%>
<%@page import="com.platform.operator.TaskOperator"%>
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>


<%
	String id = (String) session.getAttribute("id");
	String user_id = request.getParameter(
	"user_id");
	String game = request.getParameter(
	"game");
	Task task = TaskOperator.getTaskByIdAndGame(user_id, game);
%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
	<head>
		<title>compile wrong</title>
		<meta http-equiv="content-type" content="text/html; charset=utf-8" />
		
	</head>
	<body>
		<h3><%=task.getErrorInformation() %></h3>
	</body>
</html>