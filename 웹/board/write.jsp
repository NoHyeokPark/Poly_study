<%@page import="kr.ac.kopo.util.ConnectionFactory"%>
<%@page import="java.sql.Connection"%>
<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.PreparedStatement"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<% 
String title = request.getParameter("title");
String writer = request.getParameter("writer");
String content = request.getParameter("content");

PreparedStatement pstmt;
ResultSet rs;
final String id = "hr";
Connection con = new ConnectionFactory().getConn(id,id);
StringBuilder sql = new StringBuilder();
sql.append("insert into tbl_BOARD ");
sql.append(" (no, title, writer, content) ");
sql.append("values(seq_tbl_board_no.nextval, ?, ?, ?) ");

pstmt = con.prepareStatement(sql.toString());
pstmt.setString(1, title);
pstmt.setString(2, writer);
pstmt.setString(3, content);
pstmt.executeUpdate();

pstmt.close();
con.close();
%>

<script>
alert("새글등록이 완료되었습니다")
location.href = 'list.jsp'
</script>