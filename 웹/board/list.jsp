<%@page import="java.util.List"%>
<%@page import="java.util.ArrayList"%>
<%@page import="kr.ac.kopo.BoardVO"%>
<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.PreparedStatement"%>
<%@page import="java.sql.Connection"%>
<%@page import="kr.ac.kopo.util.ConnectionFactory"%>
<%@page import="javax.sql.ConnectionEvent"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="jakarta.tags.core"  %>    
<%
PreparedStatement pstmt;
ResultSet rs;
final String id = "hr";
Connection con = new ConnectionFactory().getConn(id,id);
StringBuilder sql = new StringBuilder();
sql.append("select no, title, writer, to_char(reg_date, 'yyyy-mm-dd') as reg_date2 ");
sql.append("from tbl_BOARD ");
sql.append("order by no desc ");

pstmt = con.prepareStatement(sql.toString());
rs = pstmt.executeQuery();

List<BoardVO> boardList = new ArrayList<>();

while (rs.next()){	
	BoardVO board = new BoardVO(rs.getInt("no"), rs.getString("title"), rs.getString("writer"), rs.getString("reg_date2"));
	boardList.add(board);
}
pstmt.close();
rs.close();
con.close();
//공유영역 등록
request.setAttribute("bl", boardList);

%>    
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>게시판리스트</title>
<script>
window.onload = function() {
	let addBtn = document.querySelector('#addBtn')
	addBtn.addEventListener('click', function(){
		location.href = "writeForm.jsp"
		
	})
}

</script>
</head>
<body>
<div align="center">
<hr>
<h2>전체게시판</h2>
<hr>
<table border="1" style="width:80%;">
	<tr>
		<th style="width:8%;">번호</th>
		<th >제목</th>	
		<th style="width:15%;">작성자</th>	
		<th style="width:20%;">등록일</th>	
	</tr>
	<c:forEach items="${bl}" var="i">
	<tr>
		<td >${i.no }</td>
		<td >${i.title}</td>	
		<td >${i.writer}</td>	
		<td >${i.redDate}</td>	
	</tr>
	</c:forEach>
</table>
<button id='addBtn'>새글등록</button>
</div>
</body>
</html>
<%

%>